#!/usr/bin/env node

var first10e7 = require('./build/Release/primes').gen(1e7);

console.log(first10e7.slice(-50));
