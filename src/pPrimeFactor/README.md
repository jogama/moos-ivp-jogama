# 2.680 Lab 4

Assignment is detailed [here](http://oceanai.mit.edu/ivpman/pmwiki/pmwiki.php?n=Lab.MOOSProgramming). The best ROS equivalent is probably [this tutorial](http://wiki.ros.org/ROS/Tutorials/WritingPublisherSubscriber%28c%2B%2B%29), but I wouldn't consider this a "simple" publisher. The corresponding suscriber is ```../pPrimeFactorTester```.  

pPrimeFactor is a MOOS App that finds the prime factorization of prime numbers. If it receives 173 after receiving 172359953, it should still publish the prime factorization of the later input, because it is a smaller number. Rather than calculating inputs concurrently, I just discretized the factorization and looped over each unfinished input. The inputs are provided by [poking](http://oceanai.mit.edu/ivpman/pmwiki/pmwiki.php?n=Tools.UPokeDB) the MOOS DB (similar to ROS master).  

