#pragma once
#include "Piece.h"
class King :
    public Piece
{
public:
    King(Color color, int x, int y) : Piece(color, x, y) {}
    std::string GetRepresentation() const override;
    std::pair<int, int> GetCoordinates() const;
    bool IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const override;
    std::vector<std::pair<int, int>> GetAllPosibleMoves() const override;
};

