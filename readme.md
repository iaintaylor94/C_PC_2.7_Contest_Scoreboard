# Programming Challenges
## Problem 2.7: Contest Scoreboard[^1]
### Problem description
This problem determines the position of the contestants of the "ACM ICPC" computer science competition, and prints the result to the terminal. The order of the contestants is ranked by the following criterion:

1. The number of problems solved (highest -> lowest)
2. The penalty time (lowest -> highest)
3. The team number (lowest -> highest)

There are between 1 and 100 contestants in the competition, and 9 problems to solve. Each time the contestants make a submission, it is assessed by the judge and the result of this assessment is used to calculate the score of the team. There are five types of result (L) of the assessment:

1. Correct (C)
2. Incorrect (I)
3. Clarification Request (R)
4. Unjudged (U)
5. Erroneous Submission (E)

Only the first two types affect the score of the team.

The score input to the program is formatted as follows:
team number : problem number : time : submission type (L)

The input consists of:
1. The number of cases
2. A blank line
3. Several lines of the above form (team number : problem number : time : submission type (L))
4. A blank line if more cases / No line if last case
5. Repeat (3 - 4) until all cases have been processed

The output consists of :
1. A list of the contestants with the number of problems solved and the time penalty, in order of first to last
2. A blank line if more cases / No line if last case
3. Repeat (1 - 2) until all cases have been printed



### Example 
>**Input**                                       
>1                                    
>                          
>1 2 10 I                      
>3 1 11 C                              
>1 2 19 R                       
>1 2 21 C                           
>1 1 25 C                                                                                           

>**Output**                                             
>1 2 66                                    
>3 1 11                                                                                      

### Problem solution
Each contestant will be defined as:

1. Team ID
2. Problem [9]
   1. isSolved
   2. time penalty

The teams will be ranked first by the number of questions solved, ties will be broken based on the time penalty (only for the problems solved), finally any final ties will be printed based on the team ID (lowest -> highest).

[^1]: Programming Challenges By S.Skienna and M.Revilla, page 52