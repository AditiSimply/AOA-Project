#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[16];
    int score;
} Player;

/* helper: return player with higher score */
Player maxPlayer(Player a, Player b) {
    return (a.score >= b.score) ? a : b;
}

/* helper: return highest among three players */
Player maxOfThree(Player a, Player b, Player c) {
    Player m = maxPlayer(a, b);
    return maxPlayer(m, c);
}

/* Divide & Conquer Min–Max */
Player findWinner(Player arr[], int low, int high, Player *runner_up) {
    Player sentinel = {"None", -1};

    if (low == high) {
        *runner_up = sentinel;
        return arr[low];
    }

    if (high == low + 1) {
        if (arr[low].score >= arr[high].score) {
            *runner_up = arr[high];
            return arr[low];
        } else {
            *runner_up = arr[low];
            return arr[high];
        }
    }

    int mid = (low + high) / 2;
    Player leftRunner, rightRunner;
    Player leftWinner = findWinner(arr, low, mid, &leftRunner);
    Player rightWinner = findWinner(arr, mid + 1, high, &rightRunner);

    Player finalWinner, finalLoser;
    if (leftWinner.score >= rightWinner.score) {
        finalWinner = leftWinner;
        finalLoser = rightWinner;
    } else {
        finalWinner = rightWinner;
        finalLoser = leftWinner;
    }

    *runner_up = maxOfThree(finalLoser, leftRunner, rightRunner);
    return finalWinner;
}

/* display one match visually */
Player play_match(Player p1, Player p2) {
    printf("%s (%d) vs %s (%d)\n", p1.name, p1.score, p2.name, p2.score);
    Player winner = (p1.score >= p2.score) ? p1 : p2;
    printf("Winner advancing: %s (%d)\n\n", winner.name, winner.score);
    return winner;
}

/* visual tournament */
void run_tournament_visual(Player players[], int num_players) {
    int round = 1;
    int current = num_players;

    while (current > 1) {
        printf("\n\n=== ROUND %d ===\n\n", round);
        Player next_round[current / 2];
        int j = 0;

        for (int i = 0; i < current; i += 2) {
            printf("Match %d:\n", (i / 2) + 1);
            next_round[j++] = play_match(players[i], players[i + 1]);
        }

        printf("=== ROUND %d ADVANCING PLAYERS ===\n", round);
        for (int i = 0; i < j; i++)
            printf("%s (%d)\n", next_round[i].name, next_round[i].score);

        printf("\n--- End of Round %d ---\n", round);
        if (j > 1)
            printf("Players advancing to next round: %d\n", j);

        printf("\nPress Enter to continue to next round...");
        getchar();

        for (int k = 0; k < 6; k++) printf("\n");

        for (int i = 0; i < j; i++)
            players[i] = next_round[i];

        current = j;
        round++;
    }
}

/* check if power of two */
int isPowerOfTwo(int n) {
    return n && (!(n & (n - 1)));
}

int main() {
    srand((unsigned)time(NULL));
    int num_players;

    printf("Enter number of players (must be a power of 2): ");
    if (scanf("%d", &num_players) != 1) return 0;
    getchar(); // to clear newline from buffer

    if (!isPowerOfTwo(num_players) || num_players < 2) {
        printf("Error: number must be a power of 2 (e.g., 2,4,8,16,32,64,128)\n");
        return 1;
    }

    Player *players = malloc(sizeof(Player) * num_players);
    Player *original = malloc(sizeof(Player) * num_players);

    for (int i = 0; i < num_players; i++) {
        sprintf(players[i].name, "P%03d", i + 1);
        players[i].score = rand() % 81 + 20;
        original[i] = players[i];
    }

    printf("\n=== INITIAL PLAYERS (%d total) ===\n", num_players);
    for (int i = 0; i < num_players; i++)
        printf("%s (%d)\n", players[i].name, players[i].score);

    printf("\nPress Enter to start the tournament...");
    getchar();

    run_tournament_visual(players, num_players);

    Player runner_up;
    Player winner = findWinner(original, 0, num_players - 1, &runner_up);

    printf("\n=============================\n");
    printf(" WINNER: %s (Score: %d)\n", winner.name, winner.score);
    printf(" RUNNER-UP: %s (Score: %d)\n", runner_up.name, runner_up.score);
    printf("=============================\n");

    free(players);
    free(original);
    return 0;
}
