#include "crow.h"
#include <fstream>
#include <sstream>

#include "headers/Allheader.h"

void normal_sleep(int ms) {
	clock_t startTime = clock();
	while (static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC * 1000 < ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(0));
	}
}


void sh_settings(ExecutionManager& ex, Shaker& sh, Controller& con, Speed& x, const int* X, const int* Y, const int* S,const std::string& rule_key) {
	// Инициализация контроллера
	con.initialize();

	// Настройка правила выполнения
	ex.sh_rule = std::function<void()>([&sh, &X, &Y, &S, &x]() {
		sh.move_cursor(0, *Y / 3);
		/*std::this_thread::sleep_for(std::chrono::milliseconds(10));
		sh.move_cursor(-*X, *Y);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		sh.move_cursor(*X,-*Y);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));*/

		/*sh.move_cursor(-*X, 0);
		normal_sleep(7);
		sh.move_cursor(0, *Y);
		normal_sleep(7);
		sh.move_cursor(*X, 0);
		normal_sleep(7);
		sh.move_cursor(0, -*Y);
		normal_sleep(7);*/

		sh.sendMoveCommand(-*X, 0);
		normal_sleep(7);
		sh.sendMoveCommand(0, *Y);
		normal_sleep(7);
		sh.sendMoveCommand(*X, 0);
		normal_sleep(7);
		sh.sendMoveCommand(0, -*Y);
		normal_sleep(7);
		});

	// Настройка правила проверки (используя контроллер)
	ex.tern_rule.add_rule(rule_key, [&con]() {
		return (GetKeyState(VK_RBUTTON) & 0x8000 && GetKeyState(VK_LBUTTON) & 0x8000) ||
			(con.isPressed(SDL_CONTROLLER_AXIS_TRIGGERLEFT) && con.isPressed(SDL_CONTROLLER_AXIS_TRIGGERRIGHT));
		});
}



std::string read_file(const std::string& path) {
	std::ifstream file(path);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

int main() {
	setlocale(0, "");

	//shaker initialize
	ExecutionManager ex;
	Shaker sh;
	Controller con;
	Speed speed;

	int x = 26;
	int y = 26;
	int s = 3;

	std::string rule_key = "main";

	sh_settings(ex, sh, con, speed, &x, &y, &s, rule_key);


	ex.async();



	crow::SimpleApp app;

	
	
	system("start http://localhost:8080/");



	app.loglevel(crow::LogLevel::Warning);


	// Маршрут для корневого пути "/"

	CROW_ROUTE(app, "/main.js")([]() {
		return crow::response(read_file("main.js"));
		});

	CROW_ROUTE(app, "/get_settings")([&x, &y, &s]() {
		crow::json::wvalue result;

		result["x"] = x;
		result["y"] = y;
		result["s"] = s;

		return crow::response(result);
		});


	CROW_ROUTE(app, "/update_coordinates").methods(crow::HTTPMethod::POST)([&x, &y, &s](const crow::request req) {
		auto body = crow::json::load(req.body);

		if (!body)
			return crow::response(400);
		x = body["x"].i();
		y = body["y"].i();
		s = body["s"].i();

		crow::json::wvalue result;

		result["response"] = "Succsessfully received";

		return crow::response(result);
		});

	CROW_ROUTE(app, "/style.css")([]() {
		return crow::response(read_file("style.css"));
		});

	CROW_ROUTE(app, "/")([]() {
		crow::response res(302);  // 302 - временный редирект
		res.set_header("Location", "/settings");  // Редирект на /settings
		return res;
		});

	CROW_ROUTE(app, "/settings")([]() {
		crow::response res(read_file("index.html"));
		res.add_header("Access-Control-Allow-Origin", "*");  // Разрешить CORS
		return res;
		});




	CROW_ROUTE(app, "/SendToServer").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
		auto body = crow::json::load(req.body);

		if (!body)
			return crow::response(400);

		std::string log = body["text"].s();

		std::cout << "Получено: " << log << std::endl;

		crow::json::wvalue result;

		result["response"] = "Succsessfully received";

		return crow::response(result);

		});



	// Запуск сервера на порту 8080
	app.port(8080).multithreaded().run();
}
