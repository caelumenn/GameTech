#include "../../Common/Window.h"

#include "../CSC8503Common/StateMachine.h"
#include "../CSC8503Common/StateTransition.h"
#include "../CSC8503Common/State.h"

#include "../CSC8503Common/GameServer.h"
#include "../CSC8503Common/GameClient.h"

#include "../CSC8503Common/NavigationGrid.h"

#include "TutorialGame.h"
#include "NetworkedGame.h"

using namespace NCL;
using namespace CSC8503;

void TestStateMachine() {
	StateMachine* testMachine = new StateMachine();

	int someData = 0;
	bool aData = false;

	StateFunc AFunc = [](void* data) {
		int* realData = (int*)data;
		(*realData)++;
		std::cout << "In State A!" << std::endl;
	};
	StateFunc BFunc = [](void* data) {
		int* realData = (int*)data;
		(*realData)--;
		std::cout << "In State B!" << std::endl;
	};

	StateFunc CFunc = [](void* data) {
		bool* realData = (bool*)data;
		//(*realData) = !(*realData);
		std::cout << " In State C!" << std::endl;
	};

	GenericState* stateA = new GenericState(AFunc, (void*)&someData);
	GenericState* stateB = new GenericState(BFunc, (void*)&someData);
	GenericState* stateC = new GenericState(CFunc, (void*)&aData);
	testMachine->AddState(stateA);
	testMachine->AddState(stateB);
	testMachine->AddState(stateC);

	GenericTransition<int&, int>* transitionA =
		new GenericTransition <int&, int>(GenericTransition<int&, int>::GreaterThanTransition, someData, 10, stateA, stateB); // if greater than 10 , A to B

	GenericTransition<int&, int>* transitionB =
		new GenericTransition <int&, int>(GenericTransition<int&, int>::EqualsTransition, someData, 0, stateB, stateA); // if equals 0 , B to A
	
	GenericTransition<bool&, bool>* transitionC =
		new GenericTransition <bool&, bool>(GenericTransition<bool&, bool>::EqualsTransition, aData, false, stateA, stateC);
	
	GenericTransition<bool&, bool>* transitionD =
		new GenericTransition <bool&, bool>(GenericTransition<bool&, bool>::EqualsTransition, aData, true, stateC, stateA);
	
	testMachine->AddTransition(transitionA);
	testMachine->AddTransition(transitionB);
	testMachine->AddTransition(transitionC);
	testMachine->AddTransition(transitionD);

	for (int i = 0; i < 300; ++i) {
		testMachine->Update(); // run the state machine !
		aData = !aData;
	}
	delete testMachine;
}

//class TestPacketReceiver : public PacketReceiver {
//public:
//	TestPacketReceiver(string name) {
//		this->name = name;
//	}
//
//	void ReceivePacket(int type, GamePacket* payload, int source) {
//		if (type == String_Message) {
//			StringPacket* realPacket = (StringPacket*)payload;
//			string msg = realPacket->GetStringFromData();
//			std::cout << name << " received message : " << msg << std::endl;
//		}
//	}
//protected:
//	string name;
//};


//void TestNetworking() {
//	NetworkBase::Initialise();
//
//	TestPacketReceiver serverReceiver("Server");
//	TestPacketReceiver clientReceiver("Client");
//
//	int port = NetworkBase::GetDefaultPort();
//
//	GameServer* server = new GameServer(port, 1);
//	GameClient* client = new GameClient();
//
//	server->RegisterPacketHandler(String_Message, &serverReceiver);
//	client->RegisterPacketHandler(String_Message, &clientReceiver);
//
//	bool canConnect = client -> Connect(127, 0, 0, 1, port);
//
//	for (int i = 0; i < 10; i++) {
//		server->SendGlobalPacket(StringPacket("Server says hello !" + std::to_string(i)));
//
//		client->SendPacket(StringPacket(" Client says hello ! " + std::to_string(i)));
//
//		server->UpdateServer();
//		client->UpdateClient();
//
//		std::this_thread::sleep_for(std::chrono::milliseconds(100));
//	}
//	NetworkBase::Destroy();
//}

vector<Vector3> testNodes;

void TestPathfinding() {
	NavigationGrid grid("TestGrid1.txt");
	
	NavigationPath outPath;
	
	Vector3 startPos(80, 0, 10);
	Vector3 endPos(80, 0, 80);
	
	bool found = grid.FindPath(startPos, endPos, outPath);
	
	Vector3 pos;
	while (outPath.PopWaypoint(pos)) {
		testNodes.push_back(pos);
	}
}

void DisplayPathfinding() {
	//std::cout << testNodes.size() << std::endl;
	for (int i = 1; i < testNodes.size(); ++i) {
		Vector3 a = testNodes[i - 1];
		Vector3 b = testNodes[i];
		Debug::DrawLine(a, b, Vector4(0, 1, 0, 1));
	}
}



/*

The main function should look pretty familar to you!
We make a window, and then go into a while loop that repeatedly
runs our 'game' until we press escape. Instead of making a 'renderer'
and updating it, we instead make a whole game, and repeatedly update that,
instead. 

This time, we've added some extra functionality to the window class - we can
hide or show the 

*/
int main() {
	Window*w = Window::CreateGameWindow("CSC8503 Game technology!", 1280, 720);

	if (!w->HasInitialised()) {
		return -1;
	}	

	//TestStateMachine();
	//TestNetworking();
	//TestPathfinding();
	
	w->ShowOSPointer(false);
	w->LockMouseToWindow(true);
	float maxTime = 180.0f;
	TutorialGame* g = new TutorialGame();

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KeyboardKeys::ESCAPE)) {
		
		float dt = w->GetTimer()->GetTimeDeltaSeconds();
		//maxTime -= dt;
		//std::cout << maxTime << std::endl;
		if (dt > 1.0f) {
			std::cout << "Skipping large time delta" << std::endl;
			continue; //must have hit a breakpoint or something to have a 1 second frame time!
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NEXT)) {
			w->ShowConsole(false);
		}

		//DisplayPathfinding();

		w->SetTitle("Gametech frame time:" + std::to_string(1000.0f * dt));

		g->UpdateGame(dt);
	}
	Window::DestroyGameWindow();
}