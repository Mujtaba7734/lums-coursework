#include "champions_trophy.h"
#include <algorithm>
using namespace std;

Team::Team()
{
    this->name = "";
    this->wins = 0;
    this->totalMatches = 0;
    this->players = vector<string>();
}

Team::Team(string name, vector<string> playerNames)
{
    this->name = name;
    this->players = playerNames;
    this->wins = 0;
    this->totalMatches = 0;
}

void Team::addWin()
{
    if (this->wins < 0)
    {
        return;
    }
    this->wins++;
}

void Team::addMatch()
{
    if (this->totalMatches < 0 )
    {
        return;
    }
    this->totalMatches++;
}

bool Team::hasPlayer(const string& player) const 
{
    for (auto it = this->players.begin(); it != this->players.end(); ++it)
    {
        if (*it == player)
        {
            return true;
        }
    }
    return false;
}

const vector<string>& Team::getPlayers() const 
{
    return this->players; 
}

int Team::getWinPercentage() const 
{
    if (totalMatches == 0)
    {
        cout << "No matches played" << endl;
        return 0;
    }
    float divide =(float) wins / totalMatches;  
    int percentage = (divide) * 100;
    return percentage;
}

string Team::getName() const 
{
    return this->name;
}

int Team::getWins() const 
{
    return this->wins;
}

int Team::getTotalMatches() const 
{
    return this->totalMatches;
}

Match::Match(Team t1, Team t2, int y)
{
    this->team1 = t1;
    this->team2 = t2;
    this->year = y;
    this->winner = nullptr;
}

void Match::addPerformance(string player, int runs, int wickets)
{
    if (runs < 0)
    {
        cout << "Error in runs: Negative Value" << endl;
        return;
    }
    if (wickets < 0)
    {
        cout << "Error in wickets: Negative Value" << endl;
        return;
    }

    if (playerStats.find(player) != playerStats.end())
    {
        playerStats[player].first = runs;
        playerStats[player].second = wickets;
    }
    else
    {
        playerStats[player] = {runs, wickets};
    }

}

const map<string, pair<int, int>>& Match::getPlayerStats() const 
{
    return playerStats;
}

int Match::getYear() const 
{
    return year;
}

void Match::setWinner()
{
    int totalruns1 = 0;
    int totalruns2 = 0;

    for (auto &entry : playerStats)
    {
        if (team1.hasPlayer(entry.first))
        {
            totalruns1 += entry.second.first;
        }
        if (team2.hasPlayer(entry.first))
        {
            totalruns2 += entry.second.first;
        } 
    }
    if (totalruns1 > totalruns2)
    {
        winner = &team1;
        return;
    }
    else if (totalruns1 < totalruns2)
    {
        winner = &team2;
    }
    else
    {
        cout << "The match is tied, but the winner is team 2" << endl;
        winner = &team2;
    }
}

string Match::getWinner() const 
{
    if (winner->getName() == "")
    {
        return "No winner Set";
    }
    return winner->getName();
}

const Team& Match::getTeam1() const 
{
    return team1;
}

const Team& Match::getTeam2() const 
{
    return team2;
}

void CricketDatabase::addTeam(string name, vector<string> players)
{
    //! Edge Cases
    if (name == "")
    {
        cout << "Error: No Name" << endl;
        return;
    }
    if (players.empty())
    {
        cout << "Error: No players in the team" << endl;
        return;
    }

    if (teams.find(name) != teams.end())
    {
        cout << "Error: Team already exists" << endl;
        return;
    }

    //* Main code

    teams[name] = Team(name, players);

}

bool CricketDatabase::addMatch(string team1, string team2, int year, const map<string, pair<int, int>>& performances) 
{
    //! Edge Cases
    if (teams.find(team1) == teams.end())
    {
        return false;
    }

    if (teams.find(team2) == teams.end())
    {
        return false;
    }

    if (year < 0)
    {
        return false;
    }

    //* main code

    Team t1 = teams.find(team1)->second;
    Team t2 = teams.find(team2)->second;
    matches.push_back(Match(t1, t2, year));
    
    for (auto it = performances.begin(); it != performances.end(); ++it)
    {
        matches.back().addPerformance(it->first, it->second.first, it->second.second);
        playerPerformances[it->first].push_back(it->second);
    }
    matches.back().setWinner();

    teams[team1].addMatch();
    teams[team2].addMatch();

    if (matches.back().getWinner() == team1)
    {
        teams[team1].addWin();
    }
    else
    {
        teams[team2].addWin();
    }
    
    return true;
}


bool CricketDatabase::addMatchPerformance(string player, int runs, int wickets) 
{
    //! edge cases

    if (playerPerformances.find(player) == playerPerformances.end())
    {
        return false;
    } 
    if (runs < 0)
    {
        cout << "Error in runs: Negative Value" << endl;
        return false;
    }
    if (wickets < 0)
    {
        cout << "Error in wickets: Negative Value" << endl;
        return false;
    }

    //* Main code

    playerPerformances[player].push_back({runs, wickets});
    return true;
}


vector<Match> CricketDatabase::getMatchesByYear(int year) const 
{
    vector<Match> match_year;
    for (auto it = matches.begin(); it != matches.end(); ++it)
    {
        if (it->getYear() == year)
        {
            match_year.push_back(*it);
        }
    }

    return match_year;
}

string CricketDatabase::findBestBowler() const 
{
    int totalwickets = 0;
    int maxwickets = 0;  
    string best_bowler = "";
    for (auto& entry : playerPerformances)
    {
        totalwickets = 0;
        for (auto it = entry.second.begin(); it != entry.second.end(); ++it)
        {
            totalwickets += it->second;
        }
        
        if (totalwickets > maxwickets)
        {
            maxwickets = totalwickets;
            best_bowler = entry.first;
        }
        else if (totalwickets == maxwickets)
        {
            if (entry.first < best_bowler)
            {
                best_bowler = entry.first;
            }
        }
    }

    return best_bowler;
}

string CricketDatabase::findMostConsistentPlayer() const 
{
    int totalwickets = 0;
    int totalruns = 0;
    int score = 0;

    int max_score = 0;

    string consistent_player = "";
    for (auto& entry : playerPerformances)
    {
        totalwickets = 0;
        totalruns = 0;
        score = 0;

        for (auto it = entry.second.begin(); it != entry.second.end(); ++it)
        {
            totalruns += it->first;
            totalwickets += it->second;
        }
        
        score =  (totalwickets * 25) + totalruns;

        if (score > max_score)
        {
            max_score = score;
            consistent_player = entry.first;
        }
    }

    return consistent_player;
}

string CricketDatabase::findMostRunsScorer() const 
{
    int totalruns = 0;
    int maxruns = 0;  
    string best_batsman = "";
    for (auto& entry : playerPerformances)
    {
        totalruns = 0;
        for (auto it = entry.second.begin(); it != entry.second.end(); ++it)
        {
            totalruns += it->first;
        }
        
        if (totalruns > maxruns)
        {
            maxruns = totalruns;
            best_batsman = entry.first;
        }
        else if (totalruns == maxruns)
        {
            if (entry.first < best_batsman)
            {
                best_batsman = entry.first;
            }
        }
    }

    return best_batsman;
}

string CricketDatabase::findTeamWithMostWins() const 
{
    int max_wins = 0;
    string best_team = "";
    for (auto &entry: teams)
    {
        if (entry.second.getWins() > max_wins)
        {
            max_wins = entry.second.getWins();
            best_team = entry.first;
        }    
    }

    return best_team;
}

string CricketDatabase::findTeamWithBestWinPercentage() const 
{
    int max_percentage = 0;
    string best_team = "";
    for (auto &entry: teams)
    {
        if (entry.second.getWinPercentage() > max_percentage)
        {
            max_percentage = entry.second.getWinPercentage();
            best_team = entry.first;
        }    
    }

    return best_team;
}

vector<string> CricketDatabase::getTopNBatters(int N) const 
{
    vector<pair<string, int>> total_runs_batters;
    vector<string> top_batters;

    int total_runs = 0;

    for (auto &entry: playerPerformances)
    {
        total_runs = 0;
        for (auto it = entry.second.begin(); it != entry.second.end(); ++it)
        {
            total_runs += it->first;
        }
        total_runs_batters.push_back({entry.first ,total_runs});
    }

    sort(total_runs_batters.begin(), total_runs_batters.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    
    if (N > total_runs_batters.size())
    {
        cout << "Error, N is greater than " << total_runs_batters.size() << endl;
        cout << "Returning only for N = " << total_runs_batters.size() << endl;
    
        for (int i =0; i < total_runs_batters.size(); ++i)
        {
            top_batters.push_back(total_runs_batters.at(i).first);
        }
        return top_batters;
    }

    for (int i =0; i < N; ++i)
    {
        top_batters.push_back(total_runs_batters.at(i).first);
    }

    return top_batters;
}

vector<string> CricketDatabase::getTopNBowlers(int N) const 
{
    vector<pair<string, int>> total_wickets_bowlers;
    vector<string> top_bowlers;

    int total_wickets = 0;

    for (auto &entry: playerPerformances)
    {
        total_wickets = 0;
        for (auto it = entry.second.begin(); it != entry.second.end(); ++it)
        {
            total_wickets += it->second;
        }
        total_wickets_bowlers.push_back({entry.first ,total_wickets});
    }

    sort(total_wickets_bowlers.begin(), total_wickets_bowlers.end(), [](const pair<string, int>& a, const pair<string, int>& b)
    {
        return a.second > b.second;
    });
    
    if (N > total_wickets_bowlers.size())
    {
        cout << "Error, N is greater than " << total_wickets_bowlers.size() << endl;
        cout << "Returning only for N = " << total_wickets_bowlers.size() << endl;
    
        for (int i =0; i < total_wickets_bowlers.size(); ++i)
        {
            top_bowlers.push_back(total_wickets_bowlers.at(i).first);
        }
        return top_bowlers;
    }


    for (int i =0; i < N; ++i)
    {
        top_bowlers.push_back(total_wickets_bowlers.at(i).first);
    }

    return top_bowlers;

}

vector<Match> CricketDatabase::getClosestMatches() const 
{
    int totalruns1 = 0;
    int totalruns2 = 0;
    int difference = 0;
    vector <pair<int, Match>> time_diff;
    vector <Match> match_closest;

    for (auto &it: matches)
    {
        totalruns1 = 0;
        totalruns2 = 0;
        difference = 0;
        for (auto &entry : it.getPlayerStats())
        {
            if (it.getTeam1().hasPlayer(entry.first))
            {
                totalruns1 += entry.second.first;
            }
            if (it.getTeam2().hasPlayer(entry.first))
            {
                totalruns2 += entry.second.first;
            } 
        }

        difference = totalruns1 - totalruns2;
        if (difference < 0)
        {
            difference *= -1;
        }

        time_diff.push_back({difference, it});
    }

    sort(time_diff.begin(), time_diff.end(), [](const pair<int, Match>& a, const pair<int, Match>& b)
    {
        return a.first < b.first;
    });

    for (int i = 0; i < time_diff.size(); i++)
    {
        match_closest.push_back(time_diff.at(i).second);
    }

    return match_closest;
}

// getters
map<string, Team> CricketDatabase::getTeams() const{
    return teams;
}
vector<Match> CricketDatabase::getMatches() const{
    return matches;
}
map<string, vector<pair<int, int>>> CricketDatabase::getPlayerPerformances() const{
    return playerPerformances;
}
