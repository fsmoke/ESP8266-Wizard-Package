#pragma once

namespace ESP8266ClassWizard {

	//using namespace System;
	//using namespace System::ComponentModel;
	//using namespace System::Collections;
	//using namespace System::Windows::Forms;
	//using namespace System::Drawing;

	/// <summary>
	/// Description résumée de MyForm
	/// </summary>
	public ref class MyForm : public Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

		String^ SDKREL;
		String^ SDKVER;
		String^ SDKEXAMPLE;
		String^ BaseFolder;
		bool IsFromSdk;


	protected:
		~MyForm()
		{
			if (components)	delete components;
		}
	private:

	private: System::Windows::Forms::Label^  Caption;
	private: System::Windows::Forms::Button^  BTN_OK;
	private: System::Windows::Forms::Button^  BTN_CANCEL;

	private: System::Windows::Forms::GroupBox^  GRP_SDK;
	private: System::Windows::Forms::Label^  LBL_SDKVER;
	private: System::Windows::Forms::ComboBox^  CMB_SDKVER;
	private: System::Windows::Forms::Label^  LBL_SDKREL;
	private: System::Windows::Forms::ComboBox^  CMB_SDKREL;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::GroupBox^  GRP_PROJ;
	private: System::Windows::Forms::Label^  LBL_EXAMPLE;
	private: System::Windows::Forms::ComboBox^  CMB_EXAMPLE;
	private: System::Windows::Forms::RadioButton^  RAD_PROJECT;
	private: System::Windows::Forms::RadioButton^  RAD_EMPTY;


	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->BTN_OK = (gcnew System::Windows::Forms::Button());
			this->Caption = (gcnew System::Windows::Forms::Label());
			this->GRP_SDK = (gcnew System::Windows::Forms::GroupBox());
			this->LBL_SDKVER = (gcnew System::Windows::Forms::Label());
			this->CMB_SDKVER = (gcnew System::Windows::Forms::ComboBox());
			this->LBL_SDKREL = (gcnew System::Windows::Forms::Label());
			this->CMB_SDKREL = (gcnew System::Windows::Forms::ComboBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->GRP_PROJ = (gcnew System::Windows::Forms::GroupBox());
			this->RAD_PROJECT = (gcnew System::Windows::Forms::RadioButton());
			this->RAD_EMPTY = (gcnew System::Windows::Forms::RadioButton());
			this->LBL_EXAMPLE = (gcnew System::Windows::Forms::Label());
			this->CMB_EXAMPLE = (gcnew System::Windows::Forms::ComboBox());
			this->BTN_CANCEL = (gcnew System::Windows::Forms::Button());
			this->GRP_SDK->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->GRP_PROJ->SuspendLayout();
			this->SuspendLayout();
			// 
			// BTN_OK
			// 
			this->BTN_OK->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->BTN_OK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->BTN_OK->FlatAppearance->BorderColor = System::Drawing::SystemColors::ActiveCaption;
			this->BTN_OK->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->BTN_OK->Location = System::Drawing::Point(489, 473);
			this->BTN_OK->Name = L"BTN_OK";
			this->BTN_OK->Size = System::Drawing::Size(75, 23);
			this->BTN_OK->TabIndex = 6;
			this->BTN_OK->Text = L"OK";
			this->BTN_OK->UseVisualStyleBackColor = false;
			this->BTN_OK->Click += gcnew System::EventHandler(this, &MyForm::BTN_OK_Click);
			// 
			// Caption
			// 
			this->Caption->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->Caption->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Caption->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Caption->Location = System::Drawing::Point(-2, -2);
			this->Caption->Name = L"Caption";
			this->Caption->Size = System::Drawing::Size(663, 28);
			this->Caption->TabIndex = 5;
			this->Caption->Text = L"Relentless - ESP Wizard";
			this->Caption->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// GRP_SDK
			// 
			this->GRP_SDK->Controls->Add(this->LBL_SDKVER);
			this->GRP_SDK->Controls->Add(this->CMB_SDKVER);
			this->GRP_SDK->Controls->Add(this->LBL_SDKREL);
			this->GRP_SDK->Controls->Add(this->CMB_SDKREL);
			this->GRP_SDK->Location = System::Drawing::Point(19, 34);
			this->GRP_SDK->Name = L"GRP_SDK";
			this->GRP_SDK->Size = System::Drawing::Size(271, 78);
			this->GRP_SDK->TabIndex = 20;
			this->GRP_SDK->TabStop = false;
			this->GRP_SDK->Text = L"SDK Selection";
			// 
			// LBL_SDKVER
			// 
			this->LBL_SDKVER->AutoSize = true;
			this->LBL_SDKVER->Location = System::Drawing::Point(11, 50);
			this->LBL_SDKVER->Name = L"LBL_SDKVER";
			this->LBL_SDKVER->Size = System::Drawing::Size(67, 13);
			this->LBL_SDKVER->TabIndex = 24;
			this->LBL_SDKVER->Text = L"SDK Version";
			// 
			// CMB_SDKVER
			// 
			this->CMB_SDKVER->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->CMB_SDKVER->FormattingEnabled = true;
			this->CMB_SDKVER->Location = System::Drawing::Point(80, 46);
			this->CMB_SDKVER->Name = L"CMB_SDKVER";
			this->CMB_SDKVER->Size = System::Drawing::Size(185, 21);
			this->CMB_SDKVER->TabIndex = 23;
			this->CMB_SDKVER->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::CMB_SDKVER_SelectedIndexChanged);
			// 
			// LBL_SDKREL
			// 
			this->LBL_SDKREL->AutoSize = true;
			this->LBL_SDKREL->Location = System::Drawing::Point(7, 23);
			this->LBL_SDKREL->Name = L"LBL_SDKREL";
			this->LBL_SDKREL->Size = System::Drawing::Size(71, 13);
			this->LBL_SDKREL->TabIndex = 22;
			this->LBL_SDKREL->Text = L"SDK Release";
			// 
			// CMB_SDKREL
			// 
			this->CMB_SDKREL->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->CMB_SDKREL->FormattingEnabled = true;
			this->CMB_SDKREL->Location = System::Drawing::Point(80, 19);
			this->CMB_SDKREL->Name = L"CMB_SDKREL";
			this->CMB_SDKREL->Size = System::Drawing::Size(185, 21);
			this->CMB_SDKREL->TabIndex = 21;
			this->CMB_SDKREL->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::CMB_SDKREL_SelectedIndexChanged);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(301, 38);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(344, 428);
			this->pictureBox1->TabIndex = 34;
			this->pictureBox1->TabStop = false;
			// 
			// GRP_PROJ
			// 
			this->GRP_PROJ->Controls->Add(this->RAD_PROJECT);
			this->GRP_PROJ->Controls->Add(this->RAD_EMPTY);
			this->GRP_PROJ->Controls->Add(this->LBL_EXAMPLE);
			this->GRP_PROJ->Controls->Add(this->CMB_EXAMPLE);
			this->GRP_PROJ->Enabled = false;
			this->GRP_PROJ->Location = System::Drawing::Point(19, 118);
			this->GRP_PROJ->Name = L"GRP_PROJ";
			this->GRP_PROJ->Size = System::Drawing::Size(271, 100);
			this->GRP_PROJ->TabIndex = 25;
			this->GRP_PROJ->TabStop = false;
			this->GRP_PROJ->Text = L"Project";
			// 
			// RAD_PROJECT
			// 
			this->RAD_PROJECT->AutoSize = true;
			this->RAD_PROJECT->Location = System::Drawing::Point(14, 42);
			this->RAD_PROJECT->Name = L"RAD_PROJECT";
			this->RAD_PROJECT->Size = System::Drawing::Size(116, 17);
			this->RAD_PROJECT->TabIndex = 26;
			this->RAD_PROJECT->Text = L"From SDK Example";
			this->RAD_PROJECT->UseVisualStyleBackColor = true;
			// 
			// RAD_EMPTY
			// 
			this->RAD_EMPTY->AutoSize = true;
			this->RAD_EMPTY->Location = System::Drawing::Point(14, 19);
			this->RAD_EMPTY->Name = L"RAD_EMPTY";
			this->RAD_EMPTY->Size = System::Drawing::Size(144, 17);
			this->RAD_EMPTY->TabIndex = 25;
			this->RAD_EMPTY->Text = L"Empty Project (NON-OS) ";
			this->RAD_EMPTY->UseVisualStyleBackColor = true;
			// 
			// LBL_EXAMPLE
			// 
			this->LBL_EXAMPLE->AutoSize = true;
			this->LBL_EXAMPLE->Location = System::Drawing::Point(42, 68);
			this->LBL_EXAMPLE->Name = L"LBL_EXAMPLE";
			this->LBL_EXAMPLE->Size = System::Drawing::Size(59, 13);
			this->LBL_EXAMPLE->TabIndex = 24;
			this->LBL_EXAMPLE->Text = L"Project List";
			// 
			// CMB_EXAMPLE
			// 
			this->CMB_EXAMPLE->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->CMB_EXAMPLE->FormattingEnabled = true;
			this->CMB_EXAMPLE->Location = System::Drawing::Point(102, 65);
			this->CMB_EXAMPLE->Name = L"CMB_EXAMPLE";
			this->CMB_EXAMPLE->Size = System::Drawing::Size(150, 21);
			this->CMB_EXAMPLE->TabIndex = 23;
			this->CMB_EXAMPLE->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::CMB_EXAMPLE_SelectedIndexChanged);
			// 
			// BTN_CANCEL
			// 
			this->BTN_CANCEL->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->BTN_CANCEL->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->BTN_CANCEL->FlatAppearance->BorderColor = System::Drawing::SystemColors::ActiveCaption;
			this->BTN_CANCEL->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->BTN_CANCEL->Location = System::Drawing::Point(570, 473);
			this->BTN_CANCEL->Name = L"BTN_CANCEL";
			this->BTN_CANCEL->Size = System::Drawing::Size(75, 23);
			this->BTN_CANCEL->TabIndex = 35;
			this->BTN_CANCEL->Text = L"Cancel";
			this->BTN_CANCEL->UseVisualStyleBackColor = false;
			// 
			// MyForm
			// 
			this->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->ClientSize = System::Drawing::Size(658, 508);
			this->Controls->Add(this->BTN_CANCEL);
			this->Controls->Add(this->GRP_PROJ);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->GRP_SDK);
			this->Controls->Add(this->BTN_OK);
			this->Controls->Add(this->Caption);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->GRP_SDK->ResumeLayout(false);
			this->GRP_SDK->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->GRP_PROJ->ResumeLayout(false);
			this->GRP_PROJ->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void EDt_CIE_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
		{
			if (e->KeyCode == Keys::Space)
				e->SuppressKeyPress = true;
		}
		private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
		{
			array<String^>^ ReleaseList = System::IO::Directory::GetDirectories(BaseFolder);

			for (int i = 0; i < ReleaseList->Length; i++)
				ReleaseList[i] = ReleaseList[i]->Replace(BaseFolder, "");

			this->CMB_SDKREL->Items->AddRange(ReleaseList);
		}

		private: System::Void CMB_SDKREL_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
			this->LBL_SDKVER->Enabled = true;
			this->CMB_SDKVER->Enabled = true;
			this->CMB_SDKVER->Items->Clear();
			this->CMB_SDKVER->SelectedIndex = -1;
			this->GRP_PROJ->Enabled = false;
			this->CMB_EXAMPLE->Items->Clear();
			this->CMB_EXAMPLE->SelectedIndex = -1;
			this->RAD_EMPTY->Checked = true;

			array<String^>^ VersionList = System::IO::Directory::GetDirectories(BaseFolder + this->CMB_SDKREL->SelectedItem->ToString());

			for (int i = 0; i < VersionList->Length; i++)
				VersionList[i] = VersionList[i]->Replace(BaseFolder + this->CMB_SDKREL->SelectedItem->ToString() + "\\", "");

			this->CMB_SDKVER->Items->AddRange(VersionList);
		}

		private: System::Void CMB_SDKVER_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
			this->GRP_PROJ->Enabled = true;
			this->CMB_EXAMPLE->Items->Clear();
			this->CMB_EXAMPLE->SelectedIndex = -1;
			this->RAD_EMPTY->Checked = true;

			String^ SDKExample = BaseFolder + this->CMB_SDKREL->SelectedItem->ToString() + "\\" + this->CMB_SDKVER->SelectedItem->ToString() + "\\Examples\\";
			array<String^>^ ExampleList = System::IO::Directory::GetDirectories(SDKExample);

			for (int i = 0; i < ExampleList->Length; i++)
				ExampleList[i] = ExampleList[i]->Replace(SDKExample, "");

			this->CMB_EXAMPLE->Items->AddRange(ExampleList);
		}

		private: System::Void CMB_EXAMPLE_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
			this->RAD_PROJECT->Checked = true;
		}
		
		private: System::Void BTN_OK_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			SDKVER = this->CMB_SDKVER->SelectedItem->ToString();
			SDKREL = this->CMB_SDKREL->SelectedItem->ToString();
			SDKEXAMPLE = CMB_EXAMPLE->SelectedItem ? this->CMB_EXAMPLE->SelectedItem->ToString() : "";
			IsFromSdk = this->RAD_PROJECT->Checked;
		}
};
}
