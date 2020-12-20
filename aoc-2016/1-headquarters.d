#!/usr/bin/rdmd

import std.stdio;
import std.conv;
import std.array;
import std.container.array;
import std.typecons;
import std.algorithm.searching;

enum CardinalPoint
{
	North = 0,
	East = 1,
	South = 2,
	West = 3,
}

enum Turn
{
	Left  = -1,
	Right = 1,
}

CardinalPoint turn(CardinalPoint orientation, Turn turn)
{
	return to!CardinalPoint((orientation + turn + CardinalPoint.max + 1) % (CardinalPoint.max + 1));
}

alias Position = Tuple!(int, int);

void walk(ref int x, ref int y, int blocks, CardinalPoint orientation, ref Position[] path)
{
	int x_offset = 0;
	int y_offset = 0;

	switch (orientation)
	{
		case CardinalPoint.North:
			for (int iter = 0; iter < blocks; iter++)
			{
				Position p;
				p[0] = x;
				p[1] = y + iter;
				path ~= p;
			}
			y += blocks;
			break;

		case CardinalPoint.East:
			for (int iter = 0; iter < blocks; iter++)
			{
				Position p;
				p[0] = x + iter;
				p[1] = y;
				path ~= p;
			}
			x += blocks;
			break;

		case CardinalPoint.South:
			for (int iter = 0; iter < blocks; iter++)
			{
				Position p;
				p[0] = x;
				p[1] = y - iter;
				path ~= p;
			}
			y -= blocks;
			break;

		case CardinalPoint.West:
			for (int iter = 0; iter < blocks; iter++)
			{
				Position p;
				p[0] = x - iter;
				p[1] = y;
				path ~= p;
			}
			x -= blocks;
			break;

		default:
			break;
	}
}

void main()
{
	string s = "R3, L5, R2, L2, R1, L3, R1, R3, L4, R3, L1, L1, R1, L3, R2, L3, L2, R1, R1, L1, R4, L1, L4, R3, L2, L2, R1, L1, R5, R4, R2, L5, L2, R5, R5, L2, R3, R1, R1, L3, R1, L4, L4, L190, L5, L2, R4, L5, R4, R5, L4, R1, R2, L5, R50, L2, R1, R73, R1, L2, R191, R2, L4, R1, L5, L5, R5, L3, L5, L4, R4, R5, L4, R4, R4, R5, L2, L5, R3, L4, L4, L5, R2, R2, R2, R4, L3, R4, R5, L3, R5, L2, R3, L1, R2, R2, L3, L1, R5, L3, L5, R2, R4, R1, L1, L5, R3, R2, L3, L4, L5, L1, R3, L5, L2, R2, L3, L4, L1, R1, R4, R2, R2, R4, R2, R2, L3, L3, L4, R4, L4, L4, R1, L4, L4, R1, L2, R5, R2, R3, R3, L2, L5, R3, L3, R5, L2, R3, R2, L4, L3, L1, R2, L2, L3, L5, R3, L1, L3, L4, L3";

	//string s = "L3, L3, R3, R3, R6";

	auto moves = split(s, ", ");
	int x = 0;
	int y = 0;

	CardinalPoint current_orientation = CardinalPoint.North;

	Position path[];

	foreach (move; moves)
	{
		int number = to!int(move[1 .. $]);

		if (move[0] == 'R')
		{
			current_orientation = turn(current_orientation, Turn.Right);
		}
		else
		{
			current_orientation = turn(current_orientation, Turn.Left);
		}

		//writeln(move ~ " - walk " ~ to!string(current_orientation) ~ " " ~ to!string(number) ~ " blocks");

		walk(x, y, number, current_orientation, path);
	}

	writeln(x);
	writeln(y);

	for (int i = 0; i < path.length; i++)
	{
		auto point = path[i];
		Position remainder[] = path[i + 1 .. $];

		if (canFind!((Position p1, Position p2) => (p1[0] == p2[0] && p1[1] == p2[1]))(remainder, point))
		{
			writeln(to!string(point[0]) ~ " " ~ to!string(point[1]));
			break;
		}
	}
}
