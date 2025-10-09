#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 128   // no. of players

typedef struct 
{
    int score;
    int defeated[10]; // at most log2(128) = 7 opponents
    int count;        // no. of defeated players
} Player;

int tournament(Player players[], int n, int *comparisons) 
{
    int indices[N];
    for (int i = 0; i < n; i++) 
    {
        indices[i] = i;
    }

    int size = n;
    while (size > 1) 
    {
        int newSize = 0;
        for (int i = 0; i < size; i += 2) 
        {
            (*comparisons)++;
            int a = indices[i];
            int b = indices[i+1];

            if (players[a].score > players[b].score) 
            {
                players[a].defeated[players[a].count++] = players[b].score;
                indices[newSize++] = a;
            } 
            else 
            {
                players[b].defeated[players[b].count++] = players[a].score;
                indices[newSize++] = b;
            }
        }
        size = newSize;
    }
    return indices[0];  // index of winner
}

void main() 
{
    Player players[N];
    int comparisons = 0;

    srand(time(NULL));  //random generator
    system("cls");

    // assign random scores to all 128 players
    for (int i = 0; i < N; i++) 
    {
        players[i].score = rand() % 101; // random score between 0-100
        players[i].count = 0;             // initialize defeated list
    }

    // run the tournament
    int winnerIndex = tournament(players, N, &comparisons);

    //the best among all players the winner defeated is runnerup
    int runnerUpScore = -1;
    for (int i = 0; i < players[winnerIndex].count; i++) 
    {
        if (players[winnerIndex].defeated[i] > runnerUpScore) 
        {
            runnerUpScore = players[winnerIndex].defeated[i];
        }
    }

    printf("Winner score: %d\n", players[winnerIndex].score);
    printf("Runner-up score: %d\n", runnerUpScore);
    printf("Total comparisons: %d\n", comparisons + players[winnerIndex].count);
}
