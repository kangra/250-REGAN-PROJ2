250-REGAN-PROJ2
===============

CSE250 Spring 2014, Project 2 (Netflix Challenge)

Benjamin [10:23PM EDT, 05.04.2014]
  * Both MovieBase.h and UserBase.h are completed and documented.
  * Both MovieBase.cpp and UserBase.cpp have code that *seems* to work correctly. Compiles correctly with no linkage errors after many tries.
  * Next step is developing the client file to take in information from the datasets. The string parser for u.item (movies) is set within the MovieBase class. The u.user file is (mostly) useless as the only thing we need for this project is a unique identifier. To save time, we can just have something read in the file and make a new user with an id number associated with the number of lines currently read - that way, we're using the file and could manipulate it if it became necessary, but saving massive amounts of time.
  * There is currently no method to take in from the u.data (reviews) file. We only need the first three values, however, and they're separated by a space for easy reference. They are [userID][movieID][score]. The UserBase::addReview method works if we pass the MovieBase containing object, userID, movieID, and score. It will add the values appropriately where they need to be added.
