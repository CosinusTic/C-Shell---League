/*
C Programm that simulates results from Football matches and stores them into league rankings dynamically
    Step 1 (done): Assign teams and qualities from ranged random number
    Step 2 (done): Make teams clash and determine winner
    Step 3 (done): Assign points to teams depending on match outcome
    Step 4 (done): Simplify functions for reusability
    Step 5 (done): Save points between sessions
    Step 6: Output team with most points at the top
    Step 7: Separate match results and league standings
    Step 8: Automate matches
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


typedef struct 
{
    char* Arsenal_name;
    char* Tottenham_name; 
    char* Chelsea_name;  
    char* Leicester_name;
    char* Wolves_name;
    char* NewCastle_name;

}League_names;

typedef struct 
{
    int Tottenham_points;
    int Arsenal_points;
    int Chelsea_points;
    int Leicester_points;
    int Wolves_points;
    int NewCastle_points;

}League_points;

typedef struct 
{
    int Tottenham_perf;
    int Arsenal_perf;
    int Chelsea_perf;
    int Leicester_perf;
    int Wolves_perf;
    int newCastle_perf;

} League_perf;

League_names my_league_names = {"Arsenal", "Tottenham", "Chelsea", "Leicester", "Wolverampton", "Newcastle"};
League_points my_league_points = {0, 0, 0, 0, 0, 0};
League_perf my_league_perf = {6, 5, 7, 4, 3, 3};

void delay(int seconds)
{
    seconds = CLOCKS_PER_SEC;
    clock_t start_time = clock();
    while(clock() < start_time + seconds);
}




int random_number(int max)
{
    int random = rand() % (max + 1);
    return random;
}

int team_perf(int team_max_score)
{
    int team_value = random_number(team_max_score);
    return team_value;
}

int match(int team_1_perf, int team_b_perf)
{
    int result = team_1_perf - team_b_perf;
    return result;
}

void output_scores_and_store_points(int team_a_score, int team_b_score, char* team_a_name, char* team_b_name, int* team_a_points, int* team_b_points)
{
    if(match(team_a_score, team_b_score) < 0) // team B wins
    {
        *team_a_points += 0;
        *team_b_points += 3;
        printf("%s: %d - %d %s", team_a_name, team_a_score, team_b_score, team_b_name);
    }
    else if(match(team_a_score, team_b_score) > 0) // team A wins
    {
        *team_a_points += 3;
        *team_b_points += 0;
        printf("%s: %d - %d %s", team_a_name, team_a_score, team_b_score, team_b_name);
    }
    else if(match(team_a_score, team_b_score) == 0) // Draw
    {
        *team_a_points +=1;
        *team_b_points +=1;
        printf("%s: %d - %d %s", team_a_name, team_a_score, team_b_score, team_b_name);
    }
}

void team_rankings(char* team_name, int* team_points)
{
    printf("%s: %d\n", team_name, *team_points);
}

void output_league_table(void)
{
    int n = 6; //number of league points
    int x = 6; // number of league names
    int point_arr[n];
    const char *name_arr[x];
    int team_score_sorter;
    const char* team_name_sorter;
    printf("\n....Rankings....\n");
    
    point_arr[0] = my_league_points.Arsenal_points;
    point_arr[1] = my_league_points.Tottenham_points;
    point_arr[2] = my_league_points.Chelsea_points;
    point_arr[3] = my_league_points.Leicester_points;
    point_arr[4] = my_league_points.Wolves_points;
    point_arr[5] = my_league_points.NewCastle_points;

    name_arr[0] = my_league_names.Arsenal_name;
    name_arr[1] = my_league_names.Tottenham_name;
    name_arr[2] = my_league_names.Chelsea_name;
    name_arr[3] = my_league_names.Leicester_name;
    name_arr[4] = my_league_names.Wolves_name;
    name_arr[5] = my_league_names.NewCastle_name;

    for (int i = 0; i < n; ++i) 
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (point_arr[i] < point_arr[j]) 

            {
                    team_score_sorter =  point_arr[i]; 
                    team_name_sorter =  name_arr[i];
                    point_arr[i] = point_arr[j];
                    name_arr[i] = name_arr[j];
                    point_arr[j] = team_score_sorter;
                    name_arr[j] = team_name_sorter;
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        printf("%s: %d\n", name_arr[i], point_arr[i]);
    }
}


int main()
{
    int match_day = 0;
    srand(time(NULL));
    for(int i = 0; i < 2; i++)
    {
        match_day++;
        delay(1);
        printf("\nMatch day: %d\n", match_day);
        output_scores_and_store_points( // Arsenal v Tottenham
                team_perf(my_league_perf.Arsenal_perf) , team_perf(my_league_perf.Tottenham_perf), 
                my_league_names.Arsenal_name, my_league_names.Tottenham_name, 
                &my_league_points.Arsenal_points, &my_league_points.Tottenham_points);
        printf("\n");
        output_scores_and_store_points( // Chelsea v Leicester
            team_perf(my_league_perf.Chelsea_perf), team_perf(my_league_perf.Leicester_perf),
            my_league_names.Chelsea_name, my_league_names.Leicester_name, 
            &my_league_points.Chelsea_points, &my_league_points.Leicester_points);
        printf("\n");
        output_scores_and_store_points( // Newcastly vs wolves
            team_perf(my_league_perf.newCastle_perf), team_perf(my_league_perf.Wolves_perf),
            my_league_names.NewCastle_name, my_league_names.Wolves_name,
            &my_league_points.NewCastle_points, &my_league_points.Wolves_points);
        printf("\n");
        printf("\n");
    }

    output_league_table();
    
    return 0;
}