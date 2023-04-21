#include <elang/elpch.h>
#include <iostream>
#include "test.h"


using namespace el;

int main(int argc, char* argv[])
{
	//el::EngineProjectMaker* test = new el::EngineProjectMaker;
	//el::PlatformerTest* test = new el::PlatformerTest;
	//el::PathfindingTest* test = new el::PathfindingTest();
	//ClipTest* test = new ClipTest();
	el::Test* test = new el::Test;
	//el::TweenTest* test = new el::TweenTest();
	test->run();
	return 0;
}