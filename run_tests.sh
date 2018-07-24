cd ../build-Amber-G_7_2-Debug/src/amberTest

# ./tst_ambertest rawTransactionBenchmarkTest -iterations 1
 #./tst_ambertest -iterations 1
 
 
./tst_ambertest singleRawTransactionBenchmarkTest -iterations 10000
./tst_ambertest singlePrecreatedTransactionBenchmarkTest -iterations 10000
./tst_ambertest rawTransactionBenchmarkTest -iterations 1
./tst_ambertest precreatedTransactionBenchmarkTest -iterations 1
./tst_ambertest worldInteractionBenchmarkTest -iterations 1
./tst_ambertest rawLongSTMLBindBenchmarkTest -iterations 1
./tst_ambertest precreatedLongSTMLBindBenchmarkTest  -iterations 1
./tst_ambertest rawLongScalarSTMLBindBenchmarkTest  -iterations 1
./tst_ambertest precreatedLongScalarSTMLBindBenchmarkTest  -iterations 1
