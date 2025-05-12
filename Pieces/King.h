#pragma once
#include "Piece.h"
class King :
    public Piece
{
public:
    King(Color color) : Piece(color) {}
    std::string GetRepresentation() const override;
    bool IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY) const override;
};

