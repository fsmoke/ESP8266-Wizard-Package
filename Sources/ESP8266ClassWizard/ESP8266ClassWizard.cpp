#include "stdafx.h"
#include "MyForm.h"

namespace ESP8266ClassWizard 
{
	public ref class ESP8266ClassWizard : public IWizard
	{
		private:
			DTE^ m_dte;

		public:
			MyForm MainDlg;
			String^ Destination;
			String^ ProjectName;
	
			void virtual BeforeOpeningFile(ProjectItem^ projectItem) { ; }
			void virtual ProjectFinishedGenerating(Project^ project) { ; }
			void virtual ProjectItemFinishedGenerating(ProjectItem^ projectItem) { ; }
			void virtual RunFinished()
			{
				if (MainDlg.IsFromSdk == true)
				{
					String^ SDKExample = MainDlg.BaseFolder + MainDlg.SDKREL + "\\" + MainDlg.SDKVER + "\\Examples\\" + MainDlg.SDKEXAMPLE + "\\";
					String^ Filter = "*.c;*.h;*.cpp";
					List<String^>^ ExampleFileList = gcnew List<String^>();

					for each (String^ FileFilter in Filter->Split(';'))
						ExampleFileList->AddRange(System::IO::Directory::GetFiles(SDKExample, FileFilter, IO::SearchOption::AllDirectories));

					int SelectItem = 1;
					Project^ CurrentProj;
					String^ SeekProj = Destination + "\\" + ProjectName + ".vcxproj";
					do
					{
						CurrentProj = m_dte->Solution->Projects->Item(SelectItem++);
					} 
					while (String::Compare(CurrentProj->FileName, SeekProj, true));
					
					CleanNonNeccessary(CurrentProj->ProjectItems);

					for each (String^ Source in ExampleFileList)
					{
						String^ Destination = Source->Replace(SDKExample, "");
						CurrentProj->ProjectItems->AddFromTemplate(Source, Destination);
					}
				}
			}

			void CleanNonNeccessary(ProjectItems^ BaseItem)
			{
				for (int i = 1; i <= BaseItem->Count; i++)
				{
					ProjectItem^ Items = BaseItem->Item(i);

					for (int j = 0; j < Items->FileCount; j++)
						if (Items->FileNames[j]->Contains("user_main.c") || Items->FileNames[j]->Contains("user_config.h"))
							Items->Delete();
					
					if (Items->ProjectItems != nullptr)
						CleanNonNeccessary(Items->ProjectItems);					
				}
			}

			void virtual RunStarted(Object^ automationObject, Dictionary<String^, String^>^ replacementsDictionary, WizardRunKind runKind, array<System::Object ^, 1>^ customParams)
			{
				m_dte = (DTE^)automationObject;

				Destination = replacementsDictionary["$destinationdirectory$"];
				ProjectName = replacementsDictionary["$projectname$"];

				MainDlg.BaseFolder = (String^)Registry::GetValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\ESP8266 Wizard_is1", "InstallLocation", "") + "ESPressif\\";
				if (!IO::Directory::Exists(MainDlg.BaseFolder))
				{
					MessageBox::Show("Some folder seem missing, please repair or reinstall");
					throw gcnew WizardBackoutException("");
				}
				
				/***Secure Tabale Value Between File/New & Recent ***/
				String^ SolutionName = replacementsDictionary["$specifiedsolutionname$"];

				if (!SolutionName)
					SolutionName = replacementsDictionary["$projectname$"];

				if (!replacementsDictionary["$solutiondirectory$"]->Contains(SolutionName))
					replacementsDictionary["$solutiondirectory$"] += "\\" + SolutionName;
				/*** End-Secure **************************************/

				if (MainDlg.ShowDialog() == DialogResult::Cancel)
				{
					// Where I delete Project Folder
					// After Secure It's gonna be more like this and secure gonna be removed.
					// if (replacementsDictionary["$solutiondirectory$"]->Contains(SolutionName)) delete
					System::IO::Directory::Delete(replacementsDictionary["$solutiondirectory$"], true);
					throw gcnew WizardBackoutException("");
				}	

				// add an entry to the dictionary to specify the string used for the $greeting$ token
				replacementsDictionary->Add("$SDKREL$", MainDlg.SDKREL);
				replacementsDictionary->Add("$SDKVER$", MainDlg.SDKVER);
				replacementsDictionary->Add("$ProjectExt$", "vcxproj");
			}

			bool virtual ShouldAddProjectItem(String^ filePath) { return true; }
	};
}

