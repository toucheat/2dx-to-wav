// 2dx-to-wav.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <direct.h>
#include <string>

using namespace std;

void convert(string fname, string path);

int main()
{
	WIN32_FIND_DATA FindData;
	HANDLE hFind;
	TCHAR tempPath[255];

	GetCurrentDirectory(255, tempPath);

	string path = tempPath;

	path += "\\*.2dx";

	hFind = FindFirstFile((LPCSTR)path.c_str(), &FindData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do convert(FindData.cFileName, tempPath);
		while (FindNextFile(hFind, &FindData));
	}
	else {
		cout << "No such File" << endl;
		system("pause");
		FindClose(hFind);
		return 0;
	}
	cout << "Done." << endl;
	system("pause");
	FindClose(hFind);
	return 0;
}

void convert(string fname, string path) {
	char buffer[5] = { 0 };
	int length = 0;

	string outName = fname;
	outName = outName.replace(outName.length() - 3, 3, "wav");
	string fullOutName = path + "\\WAV_converted";
	_mkdir(fullOutName.c_str());
	fullOutName += "\\" + outName;

	FILE *input, *output;
	input = fopen(fname.c_str(), "rb+");

	while (!feof(input)) {
		if (FILE *tmp = fopen(fullOutName.c_str(), "r")) {
			fclose(tmp);
			break;
		}
		while (fread(buffer, 4, 1, input) == 1) {
			if (strcmp("RIFF", buffer) == 0) {
				fread(&length, 4, 1, input);
				char* mem = (char *)malloc(length);
				fread(mem, length, 1, input);
				output = fopen(fullOutName.c_str(), "wb+");
				fwrite("RIFF", 4, 1, output);
				fwrite(&length, 4, 1, output);
				fwrite(mem, length, 1, output);
				cout << outName << " saved. size : " << length << endl;
				fclose(output);
				free(mem);
				break;
			}
		}
	}
	fclose(input);
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
