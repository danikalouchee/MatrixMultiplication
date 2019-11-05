# Matrix

## Writing Requirements <br />

**Distrubted Parallel Computing** <br /> 
*Overall Archictecure & Solution* <br />
The overall goal of the project was to modify an already existing matrix multiplier. We were able to modify it by adding new ways of multiplying the matrices through the use of parallel computing. We used OpenMP to and MPI as alternative methods of multiplying the matrices. In addition, we also used SIMD to multiply the matrices that way. After creating the following methodologies, we were able to monitor and collect data on the time it takes to multiply the matrices. After collecting the data, we were able to see which computing method was best for the most efficent matrix solution. The fastest method was MPI but this occured only in larger matrices.<br />
*Algorithm Variations* <br /> 
We used various methods/variations in order to compute and multiply the matrices: <br />
***Single Thread without parallelization***: This one seemed like it was going to be the slowest because it all ran on one thread, but we actually found out that his one is the fastest. The reasoning behind this might be because of the time it takes to switch between threads. After looking at the graph, this does seem to be the fastest method but it is not significant.  <br />
***SIMD***: This means single instruction/multiple data, and it is looping of different streams of data simultaniously. The data is put into blocks which means that all the data can be pushed at once. We used the -o3 command in order to vectorize our algorithm. We also used the o command to see how SIMD is when the algorithm is unvectorized. The -o3 cmd makes it so that the multiplication is much faster than the unvectorized version.<br />
***OpenMP***: OpenMP was a library we used to multiply matrices except this methodology actually did not use paralellism. This library did multiporgramming in order to multiply. This library was useful because it made it so that we could achieve the same goal except that we would write it in much less code. Unfortunately, we discovered even though implementing the library is easy, the amount of utilization is very high and is using too many cpu cores and not fast enough results. <br />
***MPI***: MPI or message programming interface is a very old library that we used to create yet another multiplying algorithm. This one was a multiple parallel computing methodology so we thought this would be a good impelmentation. The algorithm ran well and we saw results, the only issue was that we were having a lot of trouble implementing this one because of how old the documentation was. Overall it was simple looping code that ran 4 systems instead of 2 systems showing efficency. <br />

## Team Work <br />
**Shakthi Panneer** <br />
Shakthi was in charge of the overall project management for the project. He served as the project manager (PM) and ensured smooth and continuing progress through the course of the lab. He assigned and distrubted the tasks after understand the primary objective. In a technical manner, Shakthi was in charge of ensureing that the SIMD algorithm was tweaked and working properly. After identifying what needed to be tweaked, he was able to run a simple manual test to show that his parallel computing method for multiplcation was done properly. He also automated the matrix multiplaction so that the data could be converted into graphs. Shakthi was responsible for ensuring all the documentation including the formal write up and README.md file was filled. <br />
**Dani Kalouche** <br />
Dani was in charge of many technical jobs that were essential to determine the most efficent method. She wrote the algorithms that used the parallel computing mechanism MPO, and Wolfgang cluster without parallelization. She was able to figure out the single thread process and see how that ran the matricies and then proceeded to write the Messaging program interface(MPI) code as well. Writing this portion was very tedious as Dani had to figure out and learn out to use the MPI library which is actually aged and had old documentation. Dani was also able to setup a testing environment where other group members algorithms and methods could be tested. This made it efficent for us to figure out the best way to multiply.After her implementations, the group was very clearly able to move forward with the rest of the lab.    <br />
**Maksym Goroshko** <br />
Maksyms did heavy research and testing in order to help the rest of the group understand the lab requirements. Max was in charge of making sure the lab was reading input and making output for all of the different methods. He was also in charge of OpenMP methodology. He wrote the algorithms for that which required more research and undestanding of that library. In addition, Max was responsible for producing the graphs and all additional tasks. He was able to take the data contributed from all the outputs and Shakthi's automations to produce graphs. Max was able to successfully weave together the work the entire group made with the algorithms and centralize them so that they could feed into Dani's testing environment. <br />
**Andrey Sidorov** <br />
Since the group was able to fully implement functionality, it was up to Andrey to make sure that the results were working and smoothly done. Andrey chose the method of manual testing each function and using Dani's testing environment. In this environment he ran through each algorthim variation and checked for a correct matrix as well as the stats being properly being communicated and translated to the graph. Andrey's role was a heavy combination of quality assurance as well as communicating back bugs to the algorithm writers. 
## Full Project Life-cycle  <br />

**Project Management: Trello** <br />
We used the Trello Project Managment platform to manage, assign and keep track of tasks. <br />
Our Trello Board is located here: https://trello.com/b/lI9MhZfO/parallel-computing <br />

**Development Practice** <br />
The practice we did was tied into our agile methodology. We recognized the basis of the lab depends on the different variations of multiplying, so we made our own branches and focused on our own variations. One by one we would push our variations via draft pull requests and locking mechanisms. After Dani made the testing environment we sat down together so that we could understand how each others algorithms worked in the testing environment. Then the people in charge of the graphs took the data and produced graphs. The algorithms writers stepped back as we entered a testing and quality assurance phase. After being challenged, developers went back in to address any bugs and then the team did a final review. <br /> 
**Testing**  <br />
The testing was primarily done by one person to check the algorithms as he would be able to have a clear perspective and focused on end results. We did manual testing of the algorithms but we did it in a developed environment where we could fire off the different variations back to back. The factors and results we were looking for inlcluding speed, cores consumed, and the accuracy of results. <br />
**Implementation** <br />
We made sure that the notepad had a specific format so that when the input is put in, it will know dimensions adn what numbers to multiply. As long as the format is followed, the program's capabilities are automated. <br />
**Planning** <br />
We planned out how we were going to produce the graphs and then did automation so that they can be directly done to graphs. We have graphs as proof below. 
## Graphs <br />

![graph](https://github.com/3296f19temple/matrix-05-kalouche-panneer-goroshko-sidorov/blob/master/out.png)
