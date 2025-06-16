#pragma once
#include "Piece.h"
class King :
    public Piece
{
public:
    King(Color color, int x, int y) : Piece(color, x, y) {}
    std::string GetRepresentation() const override;
    bool IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const override;
    std::vector<std::pair<int, int>> GetAllPossibleMoves() const override;
};

