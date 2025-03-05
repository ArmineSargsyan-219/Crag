#include <iostream>
#include <vector>
#include <set>

class QueenPuzzle {
private:
    int boardSize;
    std::vector<std::vector<std::string>>* solutionBoards;
    std::vector<std::string>* currentBoard;
    std::set<int>* occupiedColumns;
    std::set<int>* majorDiagonals;
    std::set<int>* minorDiagonals;

    void searchSolutions(int row) {
        if (row == boardSize) {
            solutionBoards->push_back(*currentBoard);
            return;
        }

        for (int col = 0; col < boardSize; col++) {
            if (occupiedColumns->count(col) || majorDiagonals->count(row - col) || minorDiagonals->count(row + col))
                continue;

            (*currentBoard)[row][col] = 'Q';
            occupiedColumns->insert(col);
            majorDiagonals->insert(row - col);
            minorDiagonals->insert(row + col);

            searchSolutions(row + 1);

            (*currentBoard)[row][col] = '.';
            occupiedColumns->erase(col);
            majorDiagonals->erase(row - col);
            minorDiagonals->erase(row + col);
        }
    }

public:
    QueenPuzzle(int size) : boardSize(size) {
        solutionBoards = new std::vector<std::vector<std::string>>();
        currentBoard = new std::vector<std::string>(size, std::string(size, '.'));
        occupiedColumns = new std::set<int>();
        majorDiagonals = new std::set<int>();
        minorDiagonals = new std::set<int>();
    }

    ~QueenPuzzle() {
        delete solutionBoards;
        delete currentBoard;
        delete occupiedColumns;
        delete majorDiagonals;
        delete minorDiagonals;
    }

    void findAllSolutions() {
        searchSolutions(0);
        std::cout << "Number of Solutions: " << solutionBoards->size() << std::endl;
        displaySolutions();
    }

    void displaySolutions() {
        for (const auto& solution : *solutionBoards) {
            for (const auto& row : solution)
                std::cout << row << std::endl;
            std::cout << "-----------------\n";
        }
    }
};

int main() {
    int N;
    std::cout << "Enter the value of N: ";
    std::cin >> N;

    QueenPuzzle* puzzle = new QueenPuzzle(N);
    puzzle->findAllSolutions();
    delete puzzle;

    return 0;
}
