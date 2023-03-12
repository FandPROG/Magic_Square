#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int n;
int map[510][510];
bool check[510][510];
int asc[510][510], des[510][510];
int swap_arr[510];
int key;

void output()
{
	int i, j;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

void odd_number_squar(int sx, int sy, int m, int num)
{
	int i, j;
	map[sx + m - 1][sy + (m / 2)] = num++;
	int x = sx + m - 1, y = sy + (m / 2);
	while (1)
	{
		int dx = x + 1;
		int dy = y + 1;
		if ((dx == sx + m && dy == sy + m) || (map[dx][dy] != 0)) {
			if (map[x - 1][y] != 0 || x - 1 < sx) break;
			else map[x - 1][y] = num++;
			x--;
		}
		else if (dx >= sx + m) {
			if (map[sx][dy] != 0) break;
			x = sx;
			y++;
			map[sx][dy] = num++;
		}
		else if (dy >= sy + m) {
			if (map[dx][sy] != 0) break;
			x++;
			y = sy;
			map[dx][sy] = num++;
		}
		else {
			map[dx][dy] = num++;
			x++;
			y++;
		}
	}
}

void four_squar()
{
	int i, j;
	int num = 1;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			asc[i][j] = num++;
		}
	}
	num = n * n;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			des[i][j] = num--;
		}
	}
	int four_cnt = n / 4;
	int x = 1, y = 1;
	for (j = 0; j < four_cnt; j++) {
		for (int k = 0; k < four_cnt; k++) {
			int dx = x, dy = y + 3;
			for (i = 0; i < 4; i++) check[x + i][y + i] = 1;
			for (i = 0; i < 4; i++) check[dx + i][dy - i] = 1;
			y += 4;
		}
		y = 1;
		x += 4;
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (check[i][j] == 1) map[i][j] = asc[i][j];
			else map[i][j] = des[i][j];
		}
	}
}

void four_plus_two_squar()
{
	int i, j;
	int cnt = 0;
	int m = n / 2;
	int x = 1, y = 1;
	key = (n - 2) / 4;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			if (cnt == 0) odd_number_squar(x, y, m, 1);
			if (cnt == 1) odd_number_squar(x, y, m, 1 + ((m * m) * 2));
			if (cnt == 2) odd_number_squar(x, y, m, 1 + ((m * m) * 3));
			if (cnt == 3) odd_number_squar(x, y, m, 1 + (m * m));
			cnt++;
			y += m;
		}
		x += m;
		y = 1;
	}
	for (j = 1; j <= key; j++) {
		for (i = 1; i <= m; i++) {
			swap_arr[m + i] = map[i][j];
			swap_arr[i] = map[m + i][j];
		}
		for (i = 1; i <= n; i++) map[i][j] = swap_arr[i];
	}
	for (j = 0; j < key - 1; j++) {
		for (i = 1; i <= m; i++) {
			swap_arr[m + i] = map[i][n - j];
			swap_arr[i] = map[m + i][n - j];
		}
		for (i = 1; i <= n; i++) map[i][n - j] = swap_arr[i];
	}
	int imsi[3] = { 0, };
	imsi[0] = map[(m / 2) + 1][key];
	imsi[1] = map[(m / 2) + 1][key + 1];
	map[(m / 2) + 1][key] = map[m + ((m / 2) + 1)][key];
	map[(m / 2) + 1][key + 1] = map[m + ((m / 2) + 1)][key + 1];
	map[m + ((m / 2) + 1)][key] = imsi[0];
	map[m + ((m / 2) + 1)][key + 1] = imsi[1];
}

int main()
{
	int i, j;
	scanf("%d", &n);
	if (n % 2 == 1) {
		odd_number_squar(1, 1, n, 1);
	}
	else if (n % 4 == 0) {
		four_squar();
	}
	else {
		four_plus_two_squar();
	}
	output();
	return 0;
}