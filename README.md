# Matrix

## Writing Requirements <br />

**Distrubted Parallel Computing** <br /> 
*Overall Archictecure & Solution* <br />
The overall goal of the project was to modify an already existing matrix multiplier. We were able to modify it by adding new ways of multiplying the matrices through the use of parallel computing. We used OpenMP to and MPI as alternative methods of multiplying the matrices. In addition, we also used SIMD to multiply the matrices that way. After creating the following methodologies, we were able to monitor and collect data on the time it takes to multiply the matrices. After collecting the data, we were able to see which computing method was best for the most efficent matrix solution. <br />
*Algorithm Variations* <br /> 
We used various methods/variations in order to compute and multiply the matrices: <br />
***Single Thread without parallelization***: <br />
***SIMD***: <br />
***OpenMP***: <br />
***MPI***: <br />

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
Our Trello Board is located here: https://trello.com/b/J6Pg0Qzh/lab-5-pb-demo <br />

**Development Practice** <br />

**Testing** <br />

**Implementation** <br />

**Planning** <br />

## Graphs <br />


