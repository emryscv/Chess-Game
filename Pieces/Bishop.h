#pragma once
#include "Piece.h"
class Bishop :
    public Piece
{
public:
    Bishop(Color color) : Piece(color) {}
    std::string GetRepresentation() const override;
    bool IsValidMove(int originX, int originY, int destinationX, int destinationY) const override;
};

