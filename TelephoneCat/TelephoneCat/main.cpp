#pragma execution_character_set("utf-8")
#include <iostream>
#include <windows.h>
#include <direct.h>
// Подключаем GLFW через стандартный путь (его настроил NuGet)
#include <GLFW/glfw3.h>

// Подключаем ImGui из твоей папки
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Подключаем твое Си-ядро из папки c_core
#include "phonebook.h"
#include "filefunc.h"

// Авто-подключение системной библиотеки OpenGL Windows
#pragma comment(lib, "opengl32.lib")

int main() {

	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	// 1. Инициализация GLFW
	if (!glfwInit()) {
		std::cerr << "Не удалось инициализировать GLFW!" << std::endl;
		return -1;
	}

	// Настройки OpenGL 3.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// Создаем окно приложения
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Телефонная книга (C + ImGui)", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Включаем V-Sync (60 FPS)

						 // 2. Инициализация Dear ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark(); // Тёмная тема
	
	ImFont* font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
							  // Подключаем бэкенды ImGui
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	// Инициализируем наше C-ядро
	Phonebook pb;
	phonebook_init(&pb);
	
	loadFILE("bkup.csv", &pb);

	std::cout << " [LOG] Контактов загружено: " << pb.count << std::endl;
	// Буферы для ввода текста
	char name_buf[64] = "";
	char phone_buf[64] = "";

	// 3. Главный цикл программы (Render Loop)
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Новый кадр ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		// --- ОКНО ТЕЛЕФОННОЙ КНИГИ ---
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration
			| ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_NoBringToFrontOnFocus;
		ImGui::Begin("Телефонная книга", nullptr, window_flags);

		ImGui::InputText("Имя", name_buf, sizeof(name_buf));
		ImGui::InputText("Телефон", phone_buf, sizeof(phone_buf));

		if (ImGui::Button("Добавить контакт")) {
			if (strlen(name_buf) > 0 && strlen(phone_buf) > 0) {
				Contact c = { 0 };
				strcpy(c.name, name_buf);
				strcpy(c.number, phone_buf);

				addUser(&pb, &c); // Функция из Си-ядра!

				name_buf[0] = '\0';
				phone_buf[0] = '\0';
			}
		}

		ImGui::Separator();
		ImGui::Text("Всего контактов: %d", pb.count);

		// Таблица контактов
		if (ImGui::BeginTable("contacts_table", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
			ImGui::TableSetupColumn("Имя");
			ImGui::TableSetupColumn("Телефон");
			ImGui::TableSetupColumn("Действие");
			ImGui::TableHeadersRow();

			for (int i = 0; i < pb.count; i++) {
				ImGui::TableNextRow();

				ImGui::TableSetColumnIndex(0);
				ImGui::Text("%s", pb.contacts[i].name);

				ImGui::TableSetColumnIndex(1);
				ImGui::Text("%s", pb.contacts[i].number);

				ImGui::TableSetColumnIndex(2);
				ImGui::PushID(i);
				if (ImGui::Button("Удалить")) {
					deleteUserbyindex(&pb, i); // C core
				}
				ImGui::PopID();
			}
			ImGui::EndTable();
		}

		ImGui::End();

		// Отрисовка
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// 4. Очистка ресурсов при закрытии
	phonebook_free(&pb);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}