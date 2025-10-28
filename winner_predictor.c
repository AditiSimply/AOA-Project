#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char name[10];
    int score;
} Player;

// Function to simulate a match between two players
Player play_match(Player p1, Player p2, Player *runner_up) {
    printf("%s (%d) vs %s (%d)\n", p1.name, p1.score, p2.name, p2.score);
    Player winner, loser;

    if (p1.score > p2.score) {
        winner = p1;
        loser = p2;
    } else {
        winner = p2;
        loser = p1;
    }

    printf("Winner advancing: %s (%d)\n\n", winner.name, winner.score);

    // Track the runner-up as the last player to lose in the final round
    *runner_up = loser;

    return winner;
}

// Function to simulate the entire tournament
void run_tournament(Player players[], int num_players) {
    int round = 1;
    Player runner_up;  // To store final runner-up

    while (num_players > 1) {
        printf("\n=== ROUND %d ===\n\n", round);
        Player next_round[num_players / 2];
        int j = 0;

        // Pair players and decide winners
        for (int i = 0; i < num_players; i += 2) {
            printf("Round %d Match:\n", round);
            // Pass address of runner_up — it will be updated in the final match
            next_round[j++] = play_match(players[i], players[i + 1], &runner_up);
        }

        // Show advancing players
        printf("=== ROUND %d ADVANCING PLAYERS ===\n", round);
        for (int i = 0; i < j; i++) {
            printf("%s (%d)\n", next_round[i].name, next_round[i].score);
        }

        printf("\n--- End of Round %d ---\n", round);
        printf("Players advancing to next round: %d\n", j);
        getchar(); // Pause

        // Move winners to next round
        for (int i = 0; i < j; i++) {
            players[i] = next_round[i];
        }

        num_players = j;
        round++;
    }

    printf("\n=============================\n");
    printf(" WINNER: %s (Score: %d)\n", players[0].name, players[0].score);
    printf(" RUNNER-UP: %s (Score: %d)\n", runner_up.name, runner_up.score);
    printf("=============================\n");
}

int main() {
    srand(time(NULL));
    int num_players;

    printf("Enter number of players (must be a power of 2): ");
    scanf("%d", &num_players);
    getchar(); // clear input buffer

    Player players[num_players];

    // Assign random scores and player names
    for (int i = 0; i < num_players; i++) {
        sprintf(players[i].name, "P%03d", i + 1);
        players[i].score = rand() % 81 + 20; // random score between 20–100
    }

    printf("\n=== INITIAL PLAYERS (%d total) ===\n", num_players);
    for (int i = 0; i < num_players; i++) {
        printf("%s (%d)\n", players[i].name, players[i].score);
    }

    printf("\nPress Enter to start the tournament...");
    getchar();

    run_tournament(players, num_players);
    return 0;
}
