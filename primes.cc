#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

/* C code */
extern "C" char * gen_primes(int limit);

char * gen_primes(int limit) {
  char *sieve = (char *) malloc((limit + 2) * sizeof(char));
  memset(sieve, '1', limit + 1);
  int i, j, sq = sqrt(limit + 1);
  for (i = 2; i < sq; i++) {
    for (j = i * i; j < limit + 1; j += i) {
      sieve[j] = '0';
    }
  }
  return sieve;
}


/* C++ code */
#include <node.h>

using namespace v8;

Handle<Value> PrimeGen(const Arguments &args) {

  HandleScope scope;
  Local<Array> array = Array::New();

  int   limit = args[0]->NumberValue();
  char *sieve = gen_primes(limit);

  for (int i = 2, j = 0; i < limit + 1; i++) {
    if (sieve[i] == '1') {
      array->Set(Number::New(j++), Integer::New(i));
    }
  }

  return scope.Close(array);

}

static void Init(Handle<Object> target) {
  target->Set(String::NewSymbol("gen"),
      FunctionTemplate::New(PrimeGen)->GetFunction());
}

NODE_MODULE(primes, Init);
