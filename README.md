TimeTableScheduler
==================

This is a project in development, that will allow a school's classes and teachers to be scheduled with, minimal human intervention. 

The teachers' and their periods will be allocated using a probabilistic model.

Let's say period X has N periods in a week of 45 periods. Initially the probability of allocating a period is N/45. Similarly the average number of periods of a particular type per day is N/7 - rounded down.

If there are 2 periods of X per day, and we have allocated 2 periods already, the probability of allocating another, for the same day becomes 0 (because the average has been reached).
