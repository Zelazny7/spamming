#include <Rcpp.h>
#include <Rmath.h>
#include <R.h>
#include "Bitarray.h"
using namespace Rcpp;

// port from R to Rcpp

double clip(double x, double lo, double hi) {
  
  if (x < lo) {
    x = lo;
  } else if (x > hi) {
    x = hi;
  }
  return x;
}

double log_p_xn_i(Bitarray x, int row, double* proto) {
  
  double ll = 0;
  
  for (int i = 0; i < x.nbits; i++) {
    
    double mu = clip(proto[i], 0.0001, 0.9999);
    int xni = at(x, row, i);
    
    ll += xni * log(mu) + (1 - xni) * log(1 - mu);

  }
  return ll;
}

// Returns an updated znk matrix
void log_z_nk(Bitarray x, double** znk, double* pis, double** protos, int K) {
  // Rprintf("log_z_nk\n");
  
  for (int n = 0; n < x.nrow; n++) {
    
    double rowsum = 0;
    
    for (int k = 0; k < K; k++) {
      
      znk[n][k] = log(pis[k]) + log_p_xn_i(x, n, protos[k]);
      rowsum += exp(znk[n][k]);
      
    }
    
    // normalize by dividing by rowsums
    for (int k = 0; k < K; k++) {
      znk[n][k] -= log(rowsum);
      znk[n][k] = exp(znk[n][k]);
      
    }
    
  }
}


// Maximization Functions
void p_i(double* pis, double** znk, int K, int N) {
  
  // clear pis
  
  for (int k = 0; k < K; k++) {
    pis[k] = 0; // reset to zero
    
    for (int n = 0; n < N; n++) {
      
      pis[k] += znk[n][k];
      
    }
    
    // make sure pis are not zero or 1
    pis[k] /= N;
    
  }
  
}


void proto_i(Bitarray x, double** znk, double* proto, int k) {
  
  for (int i = 0; i < x.nbits; i++) {
    
    double num = 0;
    double den = 0;
    
    for (int n = 0; n < x.nrow; n++) {
      
      num += znk[n][k] * at(x, n, i);
      den += znk[n][k];
      
    }
    
    proto[i] = clip(num / den, 0.01, 0.99);
    
  }
    
}

double loglik(Bitarray x, double** znk, double* pis, double** protos, int K) {
  
  double ll = 0;
  
  for (int n = 0; n < x.nrow; n++) {
    
    for (int k = 0; k < K; k++) {
      
      ll += znk[n][k] * (log(pis[k]) + log_p_xn_i(x, n, protos[k]));
    }
  }
  
  return ll;
}


double* sample_pis(int K) {
  
  double* pis = (double*) calloc(K, sizeof(double));
  
  double total = 0;
  
  for (int k = 0; k < K; k++) {
    
    GetRNGstate();
    pis[k] = unif_rand() * 0.5 + 0.25;
    PutRNGstate();
    
    total += pis[k];
    
  }
  
  for (int k = 0; k < K; k++) {
    pis[k] /= total;
  }
  
  return pis;
  
}

double** sample_prototypes(Bitarray x, int K) {
  
  double** protos = (double**) calloc(K, sizeof(double*));
  for (int k = 0; k < K; k++) {
    protos[k] = (double*) calloc(x.nbits, sizeof(double));
  }
  
  // randomly sample a row from x 
  for (int k = 0; k < K; k++) {
    
    GetRNGstate();
    int row = floor(unif_rand() * x.nrow);
    PutRNGstate();
    
    // loop over bits
    for (int i = 0; i < x.nbits; i++) {
      GetRNGstate();
      double rand = unif_rand();
      PutRNGstate();
      
      protos[k][i] = 0.25*at(x, row, i) + 0.75*rand;

    }
  }
  return protos;
}

double** allocate_znk(int N, int K, int D) {
  
  double** znk = (double**) calloc(N, sizeof(double*));
  for (int n = 0; n < N; n++) {
    znk[n] = (double*) calloc(K, sizeof(double));
  
    for (int k = 0; k < K; k++) {
      znk[n][k] = 1.0/D;
    }
  }

  return znk;
}

typedef struct {
  double ** protos;
  double* pis;
  int K;
  int D;
  double ll;
} BMM_Result;


void free_BMM_Result(BMM_Result* x) {
  free(x->pis);
  for (int k = 0; k < x->K; k++) {
    free(x->protos[k]);
  }
  free(x->protos);
}

// return a struct with pis and protos?
BMM_Result em(Bitarray x, int K, int max_iter) {
  
  double** protos = sample_prototypes(x, K);
  double* pis = sample_pis(K);
  double** znk = allocate_znk(x.nrow, K, x.nbits);

  double old_ll = loglik(x, znk, pis, protos, K);
  
  int iter = 0;
  while( iter < max_iter) {
    
    // Expectation
    log_z_nk(x, znk, pis, protos, K);
    
    
    // Maximization
    p_i(pis, znk, K, x.nrow);
    
    for (int k = 0; k < K; k++) {
      proto_i(x, znk, protos[k], k);
    }
    
    double new_ll = loglik(x, znk, pis, protos, K);
    
    old_ll = new_ll;
    
    iter++;
    
  }
  
  // free everything
  
  for (int n = 0; n < x.nrow; n++) {
    free(znk[n]);
  }
  free(znk);
  
  BMM_Result result;
  
  result.protos = protos;
  result.pis = pis;
  result.D = x.nbits;
  result.K = K;
  result.ll = old_ll;
  
  return result;
  
}
