#include "Ghosts.h"
#include <thread>
#include <chrono>
#define ll long long 
#define db double
#define ld long double
#define loop(x) for(int i=0 ; i < x ; i++)
Ghosts::Ghosts() {
	g1u.loadFromFile("Media/pink-gh-U.png");
	g2u.loadFromFile("Media/orange-gh-U.png");
	g3u.loadFromFile("Media/red-gh-U.png");
	g4u.loadFromFile("Media/blue-gh-U.png");

	g1r.loadFromFile("Media/pink-gh-R.png");
	g2r.loadFromFile("Media/orange-gh-R.png");
	g3r.loadFromFile("Media/red-gh-R.png");
	g4r.loadFromFile("Media/blue-gh-R.png");

	g1l.loadFromFile("Media/pink-gh-L.png");
	g2l.loadFromFile("Media/orange-gh-L.png");
	g3l.loadFromFile("Media/red-gh-L.png");
	g4l.loadFromFile("Media/blue-gh-L.png");

	g1d.loadFromFile("Media/pink-gh-D.png");
	g2d.loadFromFile("Media/orange-gh-D.png");
	g3d.loadFromFile("Media/red-gh-D.png");
	g4d.loadFromFile("Media/blue-gh-D.png");

	pin.setTexture(g1u);
	ink.setTexture(g4u);
	bli.setTexture(g3u);
	cly.setTexture(g2u);
}
void Ghosts::moveGhost(int board[22][28], int ghosts[4][4], int pacman[2]) {

	for (int i = 0; i < 4; i++) {
		if (board[ghosts[i][0] + ghosts[i][2]][ghosts[i][1] + ghosts[i][3]] != 1) {
			ghosts[i][0] += ghosts[i][2];
			ghosts[i][1] += ghosts[i][3];
		}
		else {
			bool moved = false;
			while (!moved) {
				int r = (rand() % 4);
				if (r == 0) {
					if (board[ghosts[i][0] + 0][ghosts[i][1] + 1] != 1) { // right
						if (i == 0) {
							pin.setTexture(g1r);
						}
						else if (i == 1) {
							ink.setTexture(g4r);
						}
						else if (i == 2) {
							bli.setTexture(g3r);
						}
						else {
							cly.setTexture(g2r);
						}
						ghosts[i][2] = 0;
						ghosts[i][3] = 1;
						moved = true;
					}
				}
				else if (r == 1) {
					if (board[ghosts[i][0] + 1][ghosts[i][1] + 0] != 1) { // down
						if (i == 0) {
							pin.setTexture(g1d);
						}
						else if (i == 1) {
							ink.setTexture(g4d);
						}
						else if (i == 2) {
							bli.setTexture(g3d);
						}
						else {
							cly.setTexture(g2d);
						}
						ghosts[i][2] = 1;
						ghosts[i][3] = 0;
						moved = true;
					}
				}
				else if (r == 2) {
					if (board[ghosts[i][0] + 0][ghosts[i][1] - 1] != 1) { // left
						if (i == 0) {
							pin.setTexture(g1l);
						}
						else if (i == 1) {
							ink.setTexture(g4l);
						}
						else if (i == 2) {
							bli.setTexture(g3l);
						}
						else {
							cly.setTexture(g2l);
						}
						ghosts[i][2] = 0;
						ghosts[i][3] = -1;
						moved = true;
					}
				}
				else if (r == 3) {
					if (board[ghosts[i][0] - 1][ghosts[i][1] + 0] != 1) { // up
						if (i == 0) {
							pin.setTexture(g1u);
						}
						else if (i == 1) {
							ink.setTexture(g4u);
						}
						else if (i == 2) {
							bli.setTexture(g3u);
						}
						else {
							cly.setTexture(g2u);
						}
						ghosts[i][2] = -1;
						ghosts[i][3] = 0;
						moved = true;
					}
				}
			}
		}
	}
}
vector<pair<int, int>> findShortestPath(int board[22][28], int ghostPosition[2], int playerPosition[2]) {
	queue<pair<int, int>> q;
	vector<pair<int, int>> path;

	int dx[] = { -1, 0, 1, 0 };
	int dy[] = { 0, 1, 0, -1 };

	int visited[22][28] = { 0 };
	int parent[22][28] = { -1 };

	q.push({ ghostPosition[0], ghostPosition[1] });
	visited[ghostPosition[0]][ghostPosition[1]] = 1;

	while (!q.empty()) {
		pair<int, int> current = q.front();
		q.pop();

		if (current.first == playerPosition[0] && current.second == playerPosition[1]) {
			// Reached the player's position, reconstruct the path
			int x = current.first;
			int y = current.second;
			while (x != ghostPosition[0] || y != ghostPosition[1]) {
				path.push_back({ x, y });
				int prev_x = parent[x][y] / 100;
				int prev_y = parent[x][y] % 100;
				x = prev_x;
				y = prev_y;
			}
			reverse(path.begin(), path.end());
			return path;
		}

		for (int i = 0; i < 4; ++i) {
			int nx = current.first + dx[i];
			int ny = current.second + dy[i];

			if (nx >= 0 && nx < 22 && ny >= 0 && ny < 28 && !visited[nx][ny] && board[nx][ny] != 1) {
				q.push({ nx, ny });
				visited[nx][ny] = 1;
				parent[nx][ny] = current.first * 100 + current.second;
			}
		}
	}

	// No path found
	return path;
}
void handleGhostCollision(int ghosts[4][4], int prevGhostPositions[4][2]) {
	// Check for collisions between ghosts in the current step
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			// Check if ghosts i and j collide in the next step
			if (ghosts[i][0] + ghosts[i][2] == ghosts[j][0] && ghosts[i][1] + ghosts[i][3] == ghosts[j][1] &&
				ghosts[j][0] + ghosts[j][2] == ghosts[i][0] && ghosts[j][1] + ghosts[j][3] == ghosts[i][1]) {
				// Ghosts i and j are going to collide, so adjust their movements
				// Swap their movement directions
				int tempDirI = ghosts[i][2];
				int tempDirJ = ghosts[j][2];
				ghosts[i][2] = tempDirJ;
				ghosts[i][3] = ghosts[j][3];
				ghosts[j][2] = tempDirI;
				ghosts[j][3] = tempDirI;
			}
		}
	}
}

void Ghosts::moveGhostBFS(int board[22][28], int ghosts[4][4], int pacman[2]) {
	for (int i = 0; i < 4; i++) {
		// Get the current ghost's position
		int ghostPosition[2] = { ghosts[i][0], ghosts[i][1] };

		// Find the shortest path using BFS
		vector<pair<int, int>> shortestPath = findShortestPath(board, ghostPosition, pacman);

		// Move the ghost along the shortest path if it's not empty
		if (!shortestPath.empty()) {
			// Check if the next position is not occupied by another ghost
			int nextX = shortestPath[0].first;
			int nextY = shortestPath[0].second;
			bool collisionDetected = false;
			for (int j = 0; j < 4; j++) {
				if (i != j && ghosts[j][0] == nextX && ghosts[j][1] == nextY) {
					collisionDetected = true;
					break;
				}
			}
			// If no collision, update ghost's position and eye texture
			if (!collisionDetected) {
				ghosts[i][0] = nextX;
				ghosts[i][1] = nextY;

				// Update ghost's eye texture based on movement direction
				if (nextY > ghostPosition[1]) { // Right
					// Update texture for the ghost i
					if (i == 0) {
						pin.setTexture(g1r);
					}
					else if (i == 1) {
						ink.setTexture(g4r);
					}
					else if (i == 2) {
						bli.setTexture(g3r);
					}
					else {
						cly.setTexture(g2r);
					}
				}
				else if (nextY < ghostPosition[1]) { // Left
					// Update texture for the ghost i
					if (i == 0) {
						pin.setTexture(g1l);
					}
					else if (i == 1) {
						ink.setTexture(g4l);
					}
					else if (i == 2) {
						bli.setTexture(g3l);
					}
					else {
						cly.setTexture(g2l);
					}
				}
				else if (nextX < ghostPosition[0]) { // Up
					// Update texture for the ghost i
					if (i == 0) {
						pin.setTexture(g1u);
					}
					else if (i == 1) {
						ink.setTexture(g4u);
					}
					else if (i == 2) {
						bli.setTexture(g3u);
					}
					else {
						cly.setTexture(g2u);
					}
				}
				else if (nextX > ghostPosition[0]) { // Down
					// Update texture for the ghost i
					if (i == 0) {
						pin.setTexture(g1d);
					}
					else if (i == 1) {
						ink.setTexture(g4d);
					}
					else if (i == 2) {
						bli.setTexture(g3d);
					}
					else {
						cly.setTexture(g2d);
					}
				}
			}
		}
	}
}
int Ghosts::Loss(RenderWindow& window, int pacman[2], int ghosts[4][4], int pacDir[2], Player& p, int c) {

	if (((ghosts[0][0] == pacman[0]) && (ghosts[0][1] == pacman[1])) || ((ghosts[1][0] == pacman[0]) && (ghosts[1][1] == pacman[1])) ||
		((ghosts[2][0] == pacman[0]) && (ghosts[2][1] == pacman[1])) || ((ghosts[3][0] == pacman[0]) && (ghosts[3][1] == pacman[1]))) {
		if (c == 1) {
			pacman[0] = 10;
			pacman[1] = 3;
			ghosts[0][0] = 12;
			ghosts[0][1] = 12;
			ghosts[1][0] = 12;
			ghosts[1][1] = 15;
			ghosts[2][0] = 8;
			ghosts[2][1] = 12;
			ghosts[3][0] = 8;
			ghosts[3][1] = 15;


		}
		else if (c == 2) {
			pacman[0] = 10;
			pacman[1] = 2;
			ghosts[0][0] = 16;
			ghosts[0][1] = 12;
			ghosts[1][0] = 16;
			ghosts[1][1] = 14;
			ghosts[2][0] = 8;
			ghosts[2][1] = 12;
			ghosts[3][0] = 8;
			ghosts[3][1] = 14;
		}
		else if (c == 3) {
			pacman[0] = 1;
			pacman[1] = 1;
			ghosts[0][0] = 8;
			ghosts[0][1] = 9;
			ghosts[1][0] = 8;
			ghosts[1][1] = 18;
			ghosts[2][0] = 17;
			ghosts[2][1] = 9;
			ghosts[3][0] = 17;
			ghosts[3][1] = 18;
		}
		pacDir[0] = 0;
		pacDir[1] = 0;
		p.s.setTexture(p.pacR[0]);
		Lives++;
	}
	return Lives;
}
Ghosts::~Ghosts() {}