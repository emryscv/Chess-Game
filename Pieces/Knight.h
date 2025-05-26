#pragma once
#include "Piece.h"
class Knight :
    public Piece
{
public:
    Knight(Color color, int x, int y) : Piece(color, x, y) {}
    std::string GetRepresentation() const override;
    bool IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const override;
};

