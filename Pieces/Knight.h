#pragma once
#include "Piece.h"
class Knight :
    public Piece
{
public:
    Knight(Color color) : Piece(color) {}
    std::string GetRepresentation() const override;
    bool IsValidMove(int originX, int originY, int destinationX, int destinationY) const override;
};

