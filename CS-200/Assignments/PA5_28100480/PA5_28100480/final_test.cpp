#include <iostream>
#include "champions_trophy.h"  // Assuming your Team class is in this file
using namespace std;

// ANSI color codes for terminal output
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

float points = 0;

void printTestResult(const string& testName, bool passed, float testPoints = 1) {
    if (passed) {
        cout << GREEN << "[PASSED] " << RESET << testName << endl;
        points += testPoints;
    } else {
        cout << RED << "[FAILED] " << RESET << testName << endl;
    }
}

void testTeamClass() {
    cout << "Running Team class tests...\n";

    // 1. Team Initialization
    Team warriors("Warriors", {"Alice", "Bob", "Charlie", "David"});

    // 1.1 Team Name Retrieval
    string expectedName = "Warriors";
    string actualName = warriors.getName();
    cout << "Test 1.1: Expected team name: \"" << expectedName << "\", Actual: \"" << actualName << "\"" << endl;
    printTestResult("1.1 Team Name Retrieval", warriors.getName() == "Warriors", 0.5);
    
    // 2. Player Presence Tests
    // 2.1 Player Exists - Alice
    bool expectedAliceExists = true;
    bool actualAliceExists = warriors.hasPlayer("Alice");
    cout << "Test 2.1: Expected Alice exists: " << (expectedAliceExists ? "true" : "false") 
         << ", Actual: " << (actualAliceExists ? "true" : "false") << endl;
    printTestResult("2.1 Player Exists - Alice", warriors.hasPlayer("Alice"), 0.5);
    
    // 2.2 Player Exists - Charlie
    bool expectedCharlieExists = true;
    bool actualCharlieExists = warriors.hasPlayer("Charlie");
    cout << "Test 2.2: Expected Charlie exists: " << (expectedCharlieExists ? "true" : "false") 
         << ", Actual: " << (actualCharlieExists ? "true" : "false") << endl;
    printTestResult("2.2 Player Exists - Charlie", warriors.hasPlayer("Charlie"), 0.5);
    
    // 2.3 Player Does Not Exist - Eve
    bool expectedEveExists = false;
    bool actualEveExists = warriors.hasPlayer("Eve");
    cout << "Test 2.3: Expected Eve exists: " << (expectedEveExists ? "true" : "false") 
         << ", Actual: " << (actualEveExists ? "true" : "false") << endl;
    printTestResult("2.3 Player Does Not Exist - Eve", !warriors.hasPlayer("Eve"), 0.5);

    // 3. Initial Win & Match Count
    int expectedInitialWins = 0;
    int actualInitialWins = warriors.getWins();
    int expectedInitialMatches = 0;
    int actualInitialMatches = warriors.getTotalMatches();
    cout << "Test 3.1: Expected initial wins: " << expectedInitialWins << ", Actual: " << actualInitialWins << endl;
    cout << "Test 3.1: Expected initial matches: " << expectedInitialMatches << ", Actual: " << actualInitialMatches << endl;
    printTestResult("3.1 Initial Wins and Matches", warriors.getWins() == 0 && warriors.getTotalMatches() == 0, 2);

    // 4. Updating Matches & Wins
    warriors.addMatch();
    warriors.addMatch();
    warriors.addWin();  // 1 win out of 2 matches

    // 4.1 Wins After Update
    int expectedWinsAfterUpdate = 1;
    int actualWinsAfterUpdate = warriors.getWins();
    cout << "Test 4.1: Expected wins after update: " << expectedWinsAfterUpdate << ", Actual: " << actualWinsAfterUpdate << endl;
    printTestResult("4.1 Wins After Update", warriors.getWins() == 1);
    
    // 4.2 Matches After Update
    int expectedMatchesAfterUpdate = 2;
    int actualMatchesAfterUpdate = warriors.getTotalMatches();
    cout << "Test 4.2: Expected matches after update: " << expectedMatchesAfterUpdate << ", Actual: " << actualMatchesAfterUpdate << endl;
    printTestResult("4.2 Matches After Update", warriors.getTotalMatches() == 2);
    
    // 4.3 Win Percentage After Update
    int expectedWinPercentage = 50;
    int actualWinPercentage = warriors.getWinPercentage();
    cout << "Test 4.3: Expected win percentage: " << expectedWinPercentage << "%, Actual: " << actualWinPercentage << "%" << endl;
    printTestResult("4.3 Win Percentage After Update", warriors.getWinPercentage() == 50);

    // 5. Further Updates
    warriors.addMatch();
    warriors.addWin();  // 2 wins out of 3 matches

    // 5.1 Wins After Second Update
    int expectedWinsAfterSecondUpdate = 2;
    int actualWinsAfterSecondUpdate = warriors.getWins();
    cout << "Test 5.1: Expected wins after second update: " << expectedWinsAfterSecondUpdate << ", Actual: " << actualWinsAfterSecondUpdate << endl;
    printTestResult("5.1 Wins After Second Update", warriors.getWins() == 2);
    
    // 5.2 Matches After Second Update
    int expectedMatchesAfterSecondUpdate = 3;
    int actualMatchesAfterSecondUpdate = warriors.getTotalMatches();
    cout << "Test 5.2: Expected matches after second update: " << expectedMatchesAfterSecondUpdate << ", Actual: " << actualMatchesAfterSecondUpdate << endl;
    printTestResult("5.2 Matches After Second Update", warriors.getTotalMatches() == 3);
    
    // 5.3 Win Percentage After Second Update
    int expectedWinPercentageAfterSecondUpdate = 66;
    int actualWinPercentageAfterSecondUpdate = warriors.getWinPercentage();
    cout << "Test 5.3: Expected win percentage after second update: " << expectedWinPercentageAfterSecondUpdate << "%, Actual: " << actualWinPercentageAfterSecondUpdate << "%" << endl;
    printTestResult("5.3 Win Percentage After Second Update", warriors.getWinPercentage() == 66);

    cout << "\nTeam Class tests completed. Take a short break :)\n";
    cout << YELLOW << "Points: " << points << " / 10" << RESET << endl;
}

void testMatchClass() {
    cout << "\nRunning Match class tests...\n";

    // 1. Match Initialization (3 marks)
    Team tigers("Tigers", {"Alice", "Bob", "Charlie"});
    Team lions("Lions", {"David", "Eve", "Frank"});
    Match match(tigers, lions, 2024);

    // 1.1 Match Year Initialization
    int expectedYear = 2024;
    int actualYear = match.getYear();
    cout << "Test 1.1: Expected match year: " << expectedYear << ", Actual: " << actualYear << endl;
    printTestResult("1.1 Match Year Initialization", match.getYear() == 2024, 1);
    
    // 1.2 Player Stats Initially Empty
    bool expectedStatsEmpty = true;
    bool actualStatsEmpty = match.getPlayerStats().empty();
    cout << "Test 1.2: Expected player stats initially empty: " << (expectedStatsEmpty ? "true" : "false") 
         << ", Actual: " << (actualStatsEmpty ? "true" : "false") << endl;
    printTestResult("1.2 Player Stats Initially Empty", match.getPlayerStats().empty(), 2);

    // 2. Adding Player Performances (4 marks)
    match.addPerformance("Alice", 50, 1);
    match.addPerformance("Bob", 30, 0);
    match.addPerformance("Charlie", 20, 2);
    match.addPerformance("David", 60, 0);
    match.addPerformance("Eve", 10, 1);
    match.addPerformance("Frank", 5, 3);

    auto stats = match.getPlayerStats();
    
    // 2.1 Correct Runs Recorded for Alice
    int expectedAliceRuns = 50;
    int actualAliceRuns = stats["Alice"].first;
    cout << "Test 2.1: Expected runs for Alice: " << expectedAliceRuns << ", Actual: " << actualAliceRuns << endl;
    printTestResult("2.1 Correct Runs Recorded for Alice", stats["Alice"].first == 50, 1);
    
    // 2.2 Correct Wickets Recorded for Frank
    int expectedFrankWickets = 3;
    int actualFrankWickets = stats["Frank"].second;
    cout << "Test 2.2: Expected wickets for Frank: " << expectedFrankWickets << ", Actual: " << actualFrankWickets << endl;
    printTestResult("2.2 Correct Wickets Recorded for Frank", stats["Frank"].second == 3, 1);
    
    // 2.3 All Players' Stats Exist
    int expectedStatsSize = 6;
    int actualStatsSize = stats.size();
    cout << "Test 2.3: Expected stats size: " << expectedStatsSize << ", Actual: " << actualStatsSize << endl;
    printTestResult("2.3 All Players' Stats Exist", stats.size() == 6, 2);

    // 3. Determining the Winner (5 marks)
    match.setWinner();
    string winner = match.getWinner();
    
    // 3.1 Winner is Determined
    bool expectedWinnerNotEmpty = true;
    bool actualWinnerNotEmpty = !winner.empty();
    cout << "Test 3.1: Expected winner determined: " << (expectedWinnerNotEmpty ? "true" : "false") 
         << ", Actual: " << (actualWinnerNotEmpty ? "true" : "false") << endl;
    printTestResult("3.1 Winner is Determined", !winner.empty(), 2);
    
    // 3.2 Winning Team Correct (Tigers Expected)
    string expectedWinner = "Tigers";
    cout << "Test 3.2: Expected winner: " << expectedWinner << ", Actual: " << winner << endl;
    cout << "  (Tigers: 50+30+20 = 100, Lions: 60+10+5 = 75)" << endl;
    printTestResult("3.2 Winning Team Correct (Tigers Expected)", winner == "Tigers", 3);

    // 4. Edge Cases for Winner Selection (4 marks)
    Match tieMatch(tigers, lions, 2025);
    tieMatch.addPerformance("Alice", 50, 0);
    tieMatch.addPerformance("Bob", 20, 1);
    tieMatch.addPerformance("Charlie", 30, 2);
    tieMatch.addPerformance("David", 60, 1);
    tieMatch.addPerformance("Eve", 30, 2);
    tieMatch.addPerformance("Frank", 10, 0);
    tieMatch.setWinner();

    // 4.1 Handles Tie Case Correctly
    bool expectedTieHandled = true;
    bool actualTieHandled = !tieMatch.getWinner().empty();
    cout << "Test 4.1: Expected tie handled: " << (expectedTieHandled ? "true" : "false") 
         << ", Actual: " << (actualTieHandled ? "true" : "false") << endl;
    printTestResult("4.1 Handles Tie Case Correctly", !tieMatch.getWinner().empty(), 2);
    
    // 4.2 Correct Winner (Lions Expected)
    string expectedTieWinner = "Lions";
    string actualTieWinner = tieMatch.getWinner();
    cout << "Test 4.2: Expected winner in tie: " << expectedTieWinner << ", Actual: " << actualTieWinner << endl;
    cout << "  (Lions: 60+30+10 = 100, Tigers: 50+20+30 = 100, first team wins tie)" << endl;
    printTestResult("4.2 Correct Winner (Lions Expected)", tieMatch.getWinner() == "Lions", 2);

    // 5. Multiple Matches and Different Years (4 marks)
    Match olderMatch(lions, tigers, 2018);
    
    // 5.1 Older Match Has Correct Year
    int expectedOlderYear = 2018;
    int actualOlderYear = olderMatch.getYear();
    cout << "Test 5.1: Expected older match year: " << expectedOlderYear << ", Actual: " << actualOlderYear << endl;
    printTestResult("5.1 Older Match Has Correct Year", olderMatch.getYear() == 2018, 2);
    
    olderMatch.addPerformance("Charlie", 40, 2);
    olderMatch.addPerformance("David", 20, 1);
    
    // 5.2 Older Match Records Player Stats
    int expectedOlderStatsSize = 2;
    int actualOlderStatsSize = olderMatch.getPlayerStats().size();
    cout << "Test 5.2: Expected older match stats size: " << expectedOlderStatsSize << ", Actual: " << actualOlderStatsSize << endl;
    printTestResult("5.2 Older Match Records Player Stats", olderMatch.getPlayerStats().size() == 2, 2);

    cout << "\nMatch class tests completed.\n";
    cout << YELLOW << "Points: " << points << " / 30" << RESET << endl;
}

void testCricketDatabase() {
    cout << "\nRunning CricketDatabase tests...\n\n";

    CricketDatabase db;
    CricketDatabase db2;  
    
    // 1. Adding Teams & Matches (15 marks)
    db.addTeam("Warriors", {"Alice", "Bob"});
    db.addTeam("Strikers", {"Charlie", "David"});
    //db2.processFile("data.txt");  

    db2.addTeam("Warriors", {"Alice", "Bob"});
    db2.addTeam("Strikers", {"Charlie", "David"});

    cout << "Teams added correctly" << endl;
    
    // 1.1 Teams Added Successfully
    int expectedTeamsSize = db2.getTeams().size();
    int actualTeamsSize = db.getTeams().size();
    cout << "Test 1.1: Expected teams size: " << expectedTeamsSize << ", Actual: " << actualTeamsSize << endl;
    printTestResult("1.1 Teams Added Successfully", db.getTeams().size() == db2.getTeams().size(), 5);
    
    cout << "Teams checked correctly" << endl;
    map<string, pair<int, int>> match1Stats = {
        {"Alice", {40, 2}}, {"Bob", {30, 0}},
        {"Charlie", {50, 1}}, {"David", {20, 2}}
    };
    db.addMatch("Warriors", "Strikers", 2024, match1Stats);
    db2.addMatch("Warriors", "Strikers", 2024, match1Stats);

    cout << "Match added correctly" << endl;
    
    // 1.2 Match Successfully Added
    int expectedMatchesSize = db2.getMatches().size();
    int actualMatchesSize = db.getMatches().size();
    cout << "Test 1.2: Expected matches size: " << expectedMatchesSize << ", Actual: " << actualMatchesSize << endl;
    printTestResult("1.2 Match Successfully Added", db.getMatches().size() == db2.getMatches().size(), 5);
    
    // 1.3 Players Performance Updated
    int expectedPerformancesSize = db2.getPlayerPerformances().size();
    int actualPerformancesSize = db.getPlayerPerformances().size();
    
    cout << "Test 1.3: Expected player performances size: " << expectedPerformancesSize << ", Actual: " << actualPerformancesSize << endl;
    printTestResult("1.3 Players Performance Updated", db.getPlayerPerformances().size() == db2.getPlayerPerformances().size(), 5);

    // 2. Adding Match Performance (15 marks)
    db.addMatchPerformance("Alice", 20, 1);
    db.addMatchPerformance("David", 15, 0);
    db2.addMatchPerformance("Alice", 20, 1);
    db2.addMatchPerformance("David", 15, 0);

    auto playerPerformances = db.getPlayerPerformances();
    
    // Check performance sizes for each player
    for(auto p: playerPerformances) {
        if(p.first == "Alice") {
            int expectedAlicePerfsSize = 2;
            int actualAlicePerfsSize = p.second.size();
            cout << "Test 2.1: Expected performance count for Alice: " << expectedAlicePerfsSize << ", Actual: " << actualAlicePerfsSize << endl;
            printTestResult("2.1 Performance Updated for Alice", p.second.size() == 2, 5);
        }
        if(p.first == "David") {
            int expectedDavidPerfsSize = 2;
            int actualDavidPerfsSize = p.second.size();
            cout << "Test 2.2: Expected performance count for David: " << expectedDavidPerfsSize << ", Actual: " << actualDavidPerfsSize << endl;
            printTestResult("2.2 Performance Updated for David", p.second.size() == 2, 5);
        }
    }

    // 2.3 Handles Non-Existent Players Gracefully
    int expectedReturnValue = 0;
    int actualReturnValue = db.addMatchPerformance("chakla", 10, 2);
    cout << "Test 2.3: Expected return value for non-existent player: " << expectedReturnValue << ", Actual: " << actualReturnValue << endl;
    printTestResult("2.3 Handles Non-Existent Players Gracefully (Individually)", db.addMatchPerformance("chakla", 10, 2) == 0, 5);

    // 3. Querying Matches (10 marks)
    vector<Match> matches2024 = db.getMatchesByYear(2024);
    
    // 3.1 Retrieves Matches for Given Year
    bool expectedMatchesNotEmpty = true;
    bool actualMatchesNotEmpty = !matches2024.empty();
    cout << "Test 3.1: Expected matches not empty: " << (expectedMatchesNotEmpty ? "true" : "false") 
         << ", Actual: " << (actualMatchesNotEmpty ? "true" : "false") << endl;
    printTestResult("3.1 Retrieves Matches for Given Year", !matches2024.empty(), 5);
    
    // 3.2 Correct Year Retrieved
    if (!matches2024.empty()) {
        int expectedMatchYear = 2024;
        int actualMatchYear = matches2024[0].getYear();
        cout << "Test 3.2: Expected match year: " << expectedMatchYear << ", Actual: " << actualMatchYear << endl;
        printTestResult("3.2 Correct Year Retrieved", matches2024[0].getYear() == 2024, 5);
    } else {
        cout << "Test 3.2: Could not check match year - no matches found for 2024" << endl;
        printTestResult("3.2 Correct Year Retrieved", false, 5);
    }

    // 4. Finding Players Based on Performance (20 marks)
    string bestBowler = db.findBestBowler();
    cout << "Test 4.1: Best bowler found: " << bestBowler << endl;
    printTestResult("4.1 Best Bowler Found", !bestBowler.empty(), 5);

    string mostConsistent = db.findMostConsistentPlayer();
    cout << "Test 4.2: Most consistent player found: " << mostConsistent << endl;
    printTestResult("4.2 Most Consistent Player Found", !mostConsistent.empty(), 5);

    string topRunScorer = db.findMostRunsScorer();
    cout << "Test 4.3: Most runs scorer found: " << topRunScorer << endl;
    printTestResult("4.3 Most Runs Scorer Found", !topRunScorer.empty(), 5);

    vector<string> topBatters = db.getTopNBatters(2);
    int expectedTopBattersSize = 2;
    int actualTopBattersSize = topBatters.size();
    cout << "Test 4.4: Expected top batters size: " << expectedTopBattersSize << ", Actual: " << actualTopBattersSize << endl;
    printTestResult("4.4 Retrieves Top Batters", topBatters.size() == 2, 5);
    
    cout << "Top batters found:" << endl;
    for(auto p: topBatters) {
        cout << "- " << p << endl;
    }

    // 5. Finding Best Teams (10 marks)
    string mostWins = db.findTeamWithMostWins();
    cout << "Test 5.1: Team with most wins: " << mostWins << endl;
    printTestResult("5.1 Team with Most Wins Found", !mostWins.empty(), 5);

    string bestWinRate = db.findTeamWithBestWinPercentage();
    cout << "Test 5.2: Team with best win percentage: " << bestWinRate << endl;
    printTestResult("5.2 Team with Best Win Percentage Found", !bestWinRate.empty(), 5);

    // 6. Testing getTopBowlers (5 marks)
    vector<string> topBowlers = db.getTopNBowlers(2);
    int expectedTopBowlersSize = 2;
    int actualTopBowlersSize = topBowlers.size();
    cout << "Test 6.1: Expected top bowlers size: " << expectedTopBowlersSize << ", Actual: " << actualTopBowlersSize << endl;
    printTestResult("6.1 Retrieves Top Bowlers", topBowlers.size() == 2, 5);
    
    cout << "Top bowlers found:" << endl;
    for(auto p: topBowlers) {
        cout << "- " << p << endl;
    }

    // 7. Testing getClosestMatches (5 marks)
    vector<Match> closestMatches = db.getClosestMatches();
    int expectedClosestMatchesSize = 1;
    int actualClosestMatchesSize = closestMatches.size();
    cout << "Test 7.1: Expected closest matches size: " << expectedClosestMatchesSize << ", Actual: " << actualClosestMatchesSize << endl;
    printTestResult("7.1 Retrieves Closest Matches", closestMatches.size() == 1, 5); 

    cout << YELLOW << "\nPoints: " << points << " / 110" << RESET << endl;
}

int main() {
    testTeamClass();
    testMatchClass();
    testCricketDatabase();
    
    if(points == 110){
        cout << "All tests passed! Great job!\n";
    }
    return 0;
}