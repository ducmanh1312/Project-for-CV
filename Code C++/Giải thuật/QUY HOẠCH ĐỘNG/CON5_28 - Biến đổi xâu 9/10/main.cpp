#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return
/// @note

int calc(string str1, string str2)
{
  int n = str1.length();
  int m = str2.length();

  // Tạo bảng khoảng cách
  vector<vector<int>> distanceTable(n + 1, vector<int>(m + 1));

  // Khởi tạo bảng
  for (int i = 0; i <= n; i++) {
    distanceTable[i][0] = i;
  }
  for (int j = 0; j <= m; j++) {
    distanceTable[0][j] = j;
  }

  // Tính toán khoảng cách sửa đổi
  for(int i = 0; i < n; i++) 
  {
    for(int j = 0; j < m; j++)
    {
      if(str1[i] == str2[j])
        distanceTable[i+1][j+1] = distanceTable[i][j];
      else
        distanceTable[i+1][j+1] = 1 + min({distanceTable[i][j+1], // xoa str1
                                          distanceTable[i+1][j],  // xoa str2 = chen str1
                                          distanceTable[i][j]});  // xoa str1 & xoa str2 = thay the str1
    }
  }

  // Trả về kết quả
  return distanceTable[n][m];
}

int main()
{
	//

	//
	int test;
	cin >> test;
	while (test--)
	{
		string str1, str2;
		cin >> str1 >> str2;

		cout << calc(str1, str2) << endl;
	}
}




// int calc(string str1, string str2)
// {
//   int n = str1.length();
//   int m = str2.length();

//   // Tạo bảng khoảng cách
//   vector<vector<int>> distanceTable(n + 1, vector<int>(m + 1));

//   // Khởi tạo bảng
//   for (int i = 0; i <= n; i++) {
//     distanceTable[i][0] = i;
//   }
//   for (int j = 0; j <= m; j++) {
//     distanceTable[0][j] = j;
//   }

//   // Tính toán khoảng cách sửa đổi
//   for (int i = 1; i <= n; i++) {
//     for (int j = 1; j <= m; j++) {
//       if (str1[i - 1] == str2[j - 1]) {
//         distanceTable[i][j] = distanceTable[i - 1][j - 1];
//       } else {
//         distanceTable[i][j] = min({
//           distanceTable[i - 1][j] + 1, // Xóa
//           distanceTable[i][j - 1] + 1, // Chèn
//           distanceTable[i - 1][j - 1] + 1 // Thay thế
//         });
//       }
//     }
//   }

//   // Trả về kết quả
//   return distanceTable[n][m];
// }