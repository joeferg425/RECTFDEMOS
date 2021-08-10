# escape=`

# Use the latest Windows Server Core image with .NET Framework 4.8.
FROM mcr.microsoft.com/dotnet/framework/sdk:4.8-windowsservercore-ltsc2019

# Restore the default Windows shell for correct batch processing.
SHELL ["cmd", "/S", "/C"]

ENV VSCMD_DEBUG 1

ADD DevPrompt.bat C:\\DevPrompt.bat

ADD https://aka.ms/vs/15/release/vs_professional.exe C:\\TEMP\\vs_professional.exe

RUN `
    curl -SL --output vs_buildtools.exe https://aka.ms/vs/16/release/vs_buildtools.exe `
    `
    && (start /w vs_buildtools.exe --quiet --wait --norestart --nocache modify `
    --installPath "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools" `
    --add Microsoft.VisualStudio.Workload.AzureBuildTools `
    --add Microsoft.VisualStudio.Component.Static.Analysis.Tools `
    --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
    --add Microsoft.VisualStudio.Component.VC.CMake.Project `
    --add Microsoft.VisualStudio.Component.VC.CoreBuildTools `
    --add Microsoft.VisualStudio.Component.VC.ATLMFC `
    --add Microsoft.VisualStudio.Component.VC.ATL `
    --add Microsoft.VisualStudio.Component.Windows10SDK.16299.Desktop `
    --add Microsoft.VisualStudio.Component.Windows10SDK.16299.UWP `
    --add Microsoft.VisualStudio.Component.Windows10SDK.16299.UWP.Native `
    --add Microsoft.VisualStudio.Component.Windows10SDK `
    --add Microsoft.VisualStudio.ComponentGroup.NativeDesktop.Win81 `
    --add Microsoft.VisualStudio.Component.VC.Redist.14.Latest `
    --add Microsoft.Component.VC.Runtime.UCRTSDK `
    --add Microsoft.VisualStudio.Component.WinXP `
    || IF "%ERRORLEVEL%"=="3010" EXIT 0)

RUN setx /m PATH "%PATH%;C:\Bin" `
    && C:\TEMP\vs_professional.exe --quiet --wait --norestart --nocache `
    --add Microsoft.VisualStudio.Component.Static.Analysis.Tools `
    --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
    --add Microsoft.VisualStudio.Component.VC.CMake.Project `
    --add Microsoft.VisualStudio.Component.VC.CoreBuildTools `
    --add Microsoft.VisualStudio.Component.VC.ATLMFC `
    --add Microsoft.VisualStudio.Component.VC.ATL `
    --add Microsoft.VisualStudio.Component.Windows10SDK.16299.Desktop `
    --add Microsoft.VisualStudio.Component.Windows10SDK.16299.UWP `
    --add Microsoft.VisualStudio.Component.Windows10SDK.16299.UWP.Native `
    --add Microsoft.VisualStudio.Component.Windows10SDK `
    --add Microsoft.VisualStudio.ComponentGroup.NativeDesktop.Win81 `
    --add Microsoft.VisualStudio.Component.VC.Redist.14.Latest `
    --add Microsoft.Component.VC.Runtime.UCRTSDK `
    --add Microsoft.VisualStudio.Component.WinXP `
    || IF "%ERRORLEVEL%"=="3010" EXIT 0

# Define the entry point for the docker container.
# This entry point starts the developer command prompt and launches the PowerShell shell.
# Start developer command prompt with any other commands specified.
#ENTRYPOINT ["cmd", "/k", "DevPrompt.lnk", "&&", "powershell.exe"]

ENTRYPOINT ["cmd", "/k", "DevPrompt.bat", "&&", "powershell.exe"]

# Default to PowerShell if no other command specified.
#CMD ["powershell.exe", "-NoLogo", "-ExecutionPolicy", "Bypass"]
#CMD ["cmd", "/k", "DevPrompt.bat", "&&", "powershell.exe"]
