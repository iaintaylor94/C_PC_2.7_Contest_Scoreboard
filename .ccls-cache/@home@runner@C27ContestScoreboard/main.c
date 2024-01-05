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
};
struct team {
  int teamID;
  struct problem problems[gNumProblems];
};
struct teams {
  struct team teams[gMaxNumTeams];
};

// Declare Functions
// File Handling
void usage (char *);

// I/O
int getNumCases (FILE*);
void stripBlankLine(FILE*);
struct input getSubmission(FILE*);

void printSubmission (struct input);

// Teams
struct teams zeroTeams(void);

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

  
  // Get input
  int numCases = getNumCases(gInputFile);
  printf ("numCases = %d\n", numCases);
  stripBlankLine(gInputFile);

  for (int i = 0; i < numCases; i++) { 
    struct input submission = getSubmission(gInputFile);
    while (submission.is_valid) {
      printSubmission(submission); printf ("\n");





      
      submission = getSubmission(gInputFile);
    }
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

void printSubmission (struct input submission) {
  printf ("teamNum = %d\n", submission.teamNum);
  printf ("problemNum = %d\n", submission.problemNum);
  printf ("time_minutes = %d\n", submission.time_minutes);
  printf ("submission = %c\n", submission.submission);
  printf ("is_valid = %d\n", submission.is_valid);
}

// Teams
struct teams zeroTeams(void) {
  struct teams retTeams;
  struct team zero;
  for (int i = 0; i < gNumProblems; i++) {
    zero.problems[i].num = 0;
    zero.problems[i].solved = false;
    zero.problems[i].timePenalty = 0;
  }
  for (int i = 0; i < gMaxNumTeams; i++) {
    retTeams.teams[i] = zero;
  }
  return retTeams;
}