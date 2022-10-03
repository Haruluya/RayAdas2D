#include "RayAdas.h"
#include "Main.h"
#include "Firebird.h"

namespace Firebird {
	class FirebirdApp : public RayAdas::Application {

	public:
		FirebirdApp() {
			PushLayer(new FirebirdLayer());
		}

		~FirebirdApp() {

		}
	};


	
}

RayAdas::Application* RayAdas::CreateApplication() {
	return new Firebird::FirebirdApp();
}