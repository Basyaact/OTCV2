#include "framework.h"
#include "headers/runtime/RuntimeHandler.h"

/**
 *
 *   ---------------- o
 * | How it's works ? |
 * o ----------------
 *
 *                           |---------------|
 *                    +++++> |  Relocations  | ======+
 * |---------|        |      |---------------|       |        |-------------------------------------------|         |---------------|       |---------------------------|
 * | Segment | =======+                              -======> | Reconstruct hotpoints with new base addr  | ======> | OWN FUNCTIONS | ====> | Call Original entry point |
 * |---------|        |      |---------------|       |        |-------------------------------------------|         |---------------|       |---------------------------|
 *                    +++++> |    Imports    | ======+
 *                           |---------------|
 *
 */

//Scary but necessary.
DWORD Segment::UnsafeAllocatedPointer = 0x0;
DWORD Segment::UnsafeLibraryPointer = 0x0;
SegmentFramework::oVirtualFunctionCaller SegmentFramework::OriginalVirtualCaller = 0x0;

BOOL APIENTRY DllMain(HMODULE module, DWORD callReason, LPVOID lpReserved) {

    //ALL DOCS INSIDE FUNCTIONS, AND HEADERS.

    if (callReason == DLL_PROCESS_ATTACH) {

        Segment segment;
        Logger logger (Logger::LoggerType::CONSOLE);
        RuntimeHandler runtime (segment);

        PanicUtils::SetImportant (&Segment::UnsafeLibraryPointer, reinterpret_cast<DWORD> (module));

        //Logo. 
        logger.Info ("  ________                      ________");
        logger.Info ("  / ____/ /_  ___  ____ _      _|__  <  /");
        logger.Info (" / /   / __ \/ _ \/ __ \ | /| / //_ </ /");
        logger.Info ("/ /___/ / / /  __/ / / / |/ |/ /__/ / /");
        logger.Info ("\____/_/ /_/\___/_/ /_/|__/|__/____/_/");
        logger.Info ("SHA256$6367c48dd193d56ea7b0baad25b19455e529f5ee");
        logger.Info ("SHA1$6ca13d52ca70c883e0f0bb101e425a89e8624de51db2d2392593af6a84118090");
        logger.Info ("SHA512$c70b5dd9ebfb6f51d09d4132b7170c9d20750a7852f00680f65658f0310e810056e6763c34c9a00b0e940076f54495c169fc2302cceb312039271c43469507dc");
        logger.Info ("SHA3_512$3274f8455be84b8c7d79f9bd93e6c8520d13f6bd2855f3bb9c006ca9f3cce25d4b924d0370f8af4e27a350fd2baeef58bc37e0f4e4a403fe64c98017fa012757");

        logger.Space ();

        logger.Info ("Welcome to Onetap-crack by Anonymous-1.");
        logger.Info ("author:CHEN,Team:AnonymousME-Team1");
        logger.Space(2);
        logger.Info("Turn to the Chinese is more difficult than I thought,so this Chinese Onetap project may throw away.");
        logger.Info("By Author:CHEN,2020.5.30");
        logger.Space (2);

        logger.Info ("| [~] Extracting segment to memory....");

        runtime.ExtractSegment();
        
        logger.Info ("| [~] Reconstructing hot-points...");

        runtime.ReconstructHotPoints();
        
        logger.Info ("| [+] Wait until the framework complete routine work...");
        logger.Info ("| [~] Filling the dependency table... (~7-15 sec)");

        segment.GetFramework().CreateDependencyTable ();

        logger.Info ("| [~] Updating netvars...");

        segment.GetFramework().UpdateNetVars();

        logger.Info ("| [~] Creating hook for internal function...");

        segment.GetFramework().CreateHook();

        logger.Info ("| [~] Updating watermark...");

        //TODO: Waiting your beatiful name.
        //README: !!getenv it's a function!!. Please read docs before edit and ask questions.
        segment.GetFramework().UpdateWatermark (getenv ("USERNAME"), "AnonymousME-CHEN");
        segment.GetFramework().UpdateMenuWatermark ("CHENCRACK");

        logger.Info ("| [~] Invoking OEP...");
       
        //Make segment alive.
        runtime.InvokeOEP();

        //Hide menu for better log look.
        segment.GetFramework().SetMenuStatus (false);

        logger.Info ("| [+] CHENCRACK is initialized.");

        logger.Space ();
       
        logger.Info ("+--------+-----------------------------------+");
        logger.Info ("| Loader |                                   |");
        logger.Info ("|--------+                                   |");
        logger.Info ("|                                            |");
        logger.Info ("| CHEN - Project creator & reverse staff.    |");
        logger.Info ("| AnonymousME-Chen - Legacy & Native help.   |");
        logger.Info ("|--------------------------------------------|");
        logger.Info ("|                                            |");
        logger.Info ("|-------+------------------------------------|");
        logger.Info ("| Crack |                                    |");
        logger.Info ("|-------+                                    |");
        logger.Info ("|                                            |");
        logger.Info ("| toast - module dumper.                     |");
        logger.Info ("| wzn   - module reconstruction.             |");
        logger.Info ("| d3x   - disassembly & advice.              |");
        logger.Info ("| CHEN - Current reverse & patch staff.      |");
        logger.Info ("|--------------------------------------------|");
        logger.Info ("|                                            |");
        logger.Info ("|---------+----------------------------------|");
        logger.Info ("|  About  |                                  |");
        logger.Info ("|---------+                                  |");
        logger.Info ("|          GITHUB:                           |");
        logger.Info ("| www.github.com/Basyaact                    |");
        logger.Info ("|--------------------------------------------|");
        logger.Info ("| Donate (WeChat):                           |");
        logger.Info ("| c855f7a84057cabf3242                       |");
        logger.Info ("| Thanks:Anonymous-Team1 for Test            |");
        logger.Info ("+--------------------------------------------+");

        logger.Space (2);

    }

    return TRUE;
}