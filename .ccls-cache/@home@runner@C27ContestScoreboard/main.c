#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <math.h>

// Declare file handles
FILE *gInputFile;

// Constants
const int gMaxLineLength = 81;
const int gMaxNumTeams = 100;
const int gNumProblems = 9;
const int gTimePenalty = 20;

// Structures
struct input {
  int teamNum;
  int problemNum;
  int time_minutes;
  char submission; // C I R U E

  bool is_valid;
};
struct problem {
  int num;
  bool solved;
  int timePenalty;
  int timesIncorrect;
};
struct team {
  int teamID;
  struct problem problems[gNumProblems];
  int numSolved;
};
struct teams {
  struct team teams[gMaxNumTeams];
};
struct teams gScoreboard;

// Declare Functions
// File Handling
void usage (char *);

// I/O
int getNumCases (FILE*);
void stripBlankLine(FILE*);
struct input getSubmission(FILE*);

void processSubmission (struct input, struct teams*);

void printSubmission (struct input);

// Teams
struct teams zeroTeams(void);
void printTeam(struct team);
void debugTeams(struct teams);
void sortTeams (struct teams*);


int main(int argc, char *argv[]) {

  /*-------------------------------FILE INITIALIZATION START-----------------------------*/
  if (argc != 2) usage (argv[0]);

  if (NULL == (gInputFile = fopen(argv[1], "r"))) {
    fprintf (stderr, "inputFile: %s: %s\n", argv[1], strerror(errno));
    exit (EXIT_FAILURE);
  }
  else {
    fprintf (stderr, "%s opened for reading.\n\n" , argv[1]);
  }
  /*-------------------------------FILE INITIALIZATION END--------------------------------*/
  /*--------------------------------MAIN PROGRAM START------------------------------------*/

  // Define teams
  struct teams teams = zeroTeams();
//  debugTeams(teams);
  
  // Get input
  int numCases = getNumCases(gInputFile);
  printf ("numCases = %d\n", numCases);
  stripBlankLine(gInputFile);

  for (int i = 0; i < numCases; i++) { 
    struct input submission = getSubmission(gInputFile);
    while (submission.is_valid) {
      processSubmission (submission, &teams); 
      submission = getSubmission(gInputFile);
    }

    sortTeams (&teams);
    debugTeams(teams);
    
    teams = zeroTeams();
  }

  




  /*--------------------------------MAIN PROGRAM END--------------------------------------*/
  /*--------------------------------FILE CLEANUP START------------------------------------*/
  fclose (gInputFile);
  /*--------------------------------FILE CLEANUP END--------------------------------------*/
  
  return 0;
}

// Define Functions
// File Handling
void usage (char *cmd) {
  fprintf (stderr, "usage: %s inputFileName\n", cmd);
  exit (EXIT_SUCCESS);
}

// I/O
int getNumCases (FILE* fp) {
  int numCases;
  char line [gMaxLineLength];
  if (NULL == fgets (line, gMaxLineLength, fp)) {
    printf ("Error: %s\n", strerror(errno));
  }
  else {
    numCases = atoi (line);
  }
  return numCases;
}
void stripBlankLine(FILE* fp) {
  char line [gMaxLineLength];
  if (NULL == fgets (line, gMaxLineLength, fp)) {
    printf ("Error: %s\n", strerror(errno));
  }
}
struct input getSubmission(FILE* fp) {
  struct input retSubmission;
  char line [gMaxLineLength];
  if (NULL == fgets (line, gMaxLineLength, fp)) {
    printf ("Error: %s\n", strerror(errno));
    retSubmission.is_valid = false;
  }
  else {
    sscanf (line, "%d %d %d %c", &retSubmission.teamNum, &retSubmission.problemNum, &retSubmission.time_minutes, &retSubmission.submission);
    retSubmission.is_valid = true;
  }
  return retSubmission;
}


void processCorrect (struct input in, struct teams *to) {
  to->teams[in.teamNum - 1].problems[in.problemNum - 1].solved = true;
  to->teams[in.teamNum - 1].problems[in.problemNum - 1].timePenalty = in.time_minutes;
  to->teams[in.teamNum - 1].numSolved++;
}
void processIncorrect (struct input in, struct teams *to) {
  to->teams[in.teamNum - 1].problems[in.problemNum - 1].timesIncorrect++;
}
void processSubmission (struct input in, struct teams *to) {
  switch (in.submission) { 
    case 'C':
      processCorrect (in, to);
      //printTeam(to->teams[in.teamNum - 1]);
      break;
    case 'I':
      processIncorrect (in, to);
      //printTeam(to->teams[in.teamNum - 1]);
      break;
    case 'R':
      //printf ("Clarification Request\n\n");
      break;
    case 'U':
      //printf ("Unjudged\n\n");
      break;
    case 'E':
      //printf ("Erroneous Submission\n\n");
      break;
    default :
      //printf ("Error: %s\n\n", strerror(errno));
    break;
  }
}



void printSubmission (struct input submission) {
  printf ("teamNum = %d\n", submission.teamNum);
  printf ("problemNum = %d\n", submission.problemNum);
  printf ("time_minutes = %d\n", submission.time_minutes);
  printf ("submission = %c\n", submission.submission);
  printf ("is_valid = %d\n", submission.is_valid);
}

// Teams
struct team zeroTeam (int teamID) {
  struct team zero;
  zero.teamID = teamID;
  zero.numSolved = 0;
  for (int i = 0; i < gNumProblems; i++) {
    zero.problems[i].num = i;
    zero.problems[i].solved = false;
    zero.problems[i].timePenalty = 0;
    zero.problems[i].timesIncorrect = 0;
  }
  return zero;
}
struct teams zeroTeams(void) {
  struct teams retTeams;

  for (int i = 0; i < gMaxNumTeams; i++) {
    retTeams.teams[i] = zeroTeam(i + 1);
  }
  return retTeams;
}
void printTeam(struct team t) {
  printf ("teamID = %d\n", t.teamID);
  for (int i = 0; i < gNumProblems; i++) {
    printf ("\tproblemNum = %d\n", t.problems[i].num);
    if (t.problems[i].solved == true) {
      printf ("\t\tsolved = true\n");
    }
    else {
      printf ("\t\tsolved = false\n");
    }
    printf ("\t\ttimesIncorrect = %d\n", t.problems[i].timesIncorrect);
    printf ("\t\ttimePenalty = %d\n", t.problems[i].timePenalty);
  }  
  printf ("\t\tnumSolved = %d\n\n", t.numSolved);
}
void debugTeams(struct teams t) {
  for (int i = 0; i < gMaxNumTeams; i++) {
    if (t.teams[i].numSolved > 0) {
      printf ("teamID = %3d\tCOMPETING\n", t.teams[i].teamID);
      printf ("numSolved = %d\n", t.teams[i].numSolved);

      for (int j = 0; j < gNumProblems; j++) {
        printf ("problemNum = %d\n", j);
        if (t.teams[i].problems[j].solved == true) {
          printf ("\tsolved = true\n");
          printf ("\ttimePenalty = %d\n", t.teams[i].problems[j].timePenalty);
          printf ("\ttimesIncorrect = %d\n", t.teams[i].problems[j].timesIncorrect);
        }
        else {
          printf ("\tsolved = false\n");
        }
      }

      printf ("\n");
    }
    else {
      printf ("teamID = %3d\tNOT COMPETING\n", t.teams[i].teamID);
      printf ("numSolved = %d\n\n", t.teams[i].numSolved);
    }
  }
}
int processNumSolved(struct team a, struct team b) {
  if (a.numSolved > b.numSolved) {
    return 1;
  }
  else if (a.numSolved < b.numSolved) {
    return -1;
  }
  else {
    return 0;
  }
}
int penalty (struct team t) {
  int pen = 0;
  for (int i = 0; i < gNumProblems; i++) {
    if (t.problems[i].solved == true) {
      pen += t.problems[i].timePenalty;
      pen += t.problems[i].timesIncorrect * gTimePenalty;
    }
  }
  return pen;
}
int processPenaltyTime(struct team a, struct team b) {
  int penaltyA = penalty (a);
  int penaltyB = penalty (b);

  if (penaltyA > penaltyB) {
    return -1;
  }
  else if (penaltyA < penaltyB) {
    return 1;
  }
  else {
    return 0;
  }
}
int processTeamID (struct team a, struct team b) {
  if (a.teamID > b.teamID) {
    return -1;
  }
  else if (a.teamID < b.teamID) {
    return 1;
  }
  else {
    return 0;
  }
}
int compareTeams (const void *a, const void *b) {
  struct team *teamA = (struct team *) a;
  struct team *teamB = (struct team *) b;

  if (processNumSolved(*teamA, *teamB) == 1) {
    return -1;
  }
  else if (processNumSolved(*teamA, *teamB) == -1) {
    return 1;
  }
  else {
    if (processPenaltyTime(*teamA, *teamB) == 1) {
      return -1;
    }
    else if (processPenaltyTime(*teamA, *teamB) == -1) {
      return 1;
    }
    else {
      if (processTeamID(*teamA, *teamB) == 1) {
        return -1;
      }
      else if (processTeamID(*teamA, *teamB) == -1) {
        return 1;
      }
      else {
        return 0;
      }
    }
  }
}
void sortTeams (struct teams *t) {
  qsort(t->teams, gMaxNumTeams, sizeof(struct team), compareTeams);
}