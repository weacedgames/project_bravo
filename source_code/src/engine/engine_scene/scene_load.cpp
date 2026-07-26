////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | //
//                      ---WEACEDGAMES PERSONNEL---                       //
//                                                                        //
//                                                                        //
// SUMMARY METADATA:                                                      //
// -> Company: WeAcEd GaMeS                                               //
// -> Author First Name: The                                              //
// -> Author Last Name: StoneUFODude                                      //
// -> Version: version.alpha.1.0                                          //
// -> File: scene_load.cpp                                                //
// -> Date Created: 07-25-2026                                            //
// -> Date Updated: 07-25-2026                                            //
//                                                                        //
// SUMMARY DESCRIPTION:                                                   //
// -> This is class loads the entity file. This entity file tells         //
// the engine how to build a scene. Like how to translate, rotate,        //
// and scale the entity.                                                  //
//                                                                        //
// SUMARRY NOTES:                                                         //
// -> I eventually want the plain text file that is read in to be         //
// converted into a JSON file. This will make the the file more stable.   //
//                                                                        //
//                                                                        //
//                      ---WEACEDGAMES PERSONNEL---                       //
//  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | //
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
///                                    ---START OF COMPANY TRANSMISSION---                                 ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    DATE: 07/01/2525        TIME: 07:00 AM                  EMAILID: 0000 0000 0000 0000 0000           ///
///                                                                                                        ///
///    UNREAD: [X]             READ: [ ]                                                                   ///
///                                                                                                        ///
///    SENDER:                                                                                             ///
///        STONEDUFODUDE@WEACEDGAMES.COM                                                                   ///
///                                                                                                        ///
///    RECIPIENT:                                                                                          ///
///        EXECUTIVE@WEACEDGAMES.COM                                                                       ///
///                                                                                                        ///
///    SUBJECT:                                                                                            ///
///        LET ME GET THIS STRAIGHT!?!?                                                                    ///
///                                                                                                        ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                    ---BODY OF COMPANY TRANSMISSION---                                  ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    MESSAGE:                                                                                            ///
///        DEAR EXECUTIVE,                                                                                 ///
///            YOUR TELLING ME... YOU WANT A CUSTOM GAME ENGINE WITH MULTIPLAYER                           ///
///            AND A GAME DEMO IN LESS THAN A YEAR ???                                                     ///
///                                                                                                        ///
///            YOU DO UNDERSTAND THAT I ...                                                                ///
///            A NEVER WORKED IN THE SOFTWARE INDUSTRY                                                     ///
///            B NEVER MADE A GAME                                                                         ///
///            C MOST IMPORTANTLY NEVER FUCKING MADE A GAME ENGINE RIGHT !?!?                              ///
///                                                                                                        ///
///            THE JOB POSTING SAID JUNIOR SOFTWARE ENGINEER WANTED, MININIUM WAGE                         ///
///            I WAS EXPECTING TO BE TAUGHT BY MOTHERFUCKERS WITH SOME EXPIERENCE                          ///
///            YOU SAID NOTHING ABOUT CLIMBING MOUNT "GO FUCK YOURSELF PROGRAMMER"                         ///
///            YOU SAID NOTHING ABOUT WORKING ON PROJECT "THERE GOES MY SANITY"                            ///
///                                                                                                        ///
///            WHAT COCAINE BENDER NIGHT DID YOU CONCIEVE THIS MOSTROSITY IDEA FROM                        ///
///            WNO IS THE SUCCUBUS THAT POSSESED YOU TO EVEN THINKING OF ATTEMPTING SUCH A                 ///
///            JOURNEY                                                                                     ///
///                                                                                                        ///
///            DID YOU BULLSHIT YOUR WAY TO GETTING THE MONEY TO PAY ME                                    ///
///            ARE YOU LIVING PROOF THAT EVEN A DUMBASSES CAN SUCCEED IN FINDING A SUCKER???               ///
///                                                                                                        ///
///                                                                                                        ///
///    SINGNATURE:                                                                                         ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                                                                                        ///
///    SOURCE:                                                                                             ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///    DESTINATION:                                                                                        ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///                                    ---END OF COMPANY TRANSMISSION---                                   ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
///                                    ---START OF COMPANY TRANSMISSION---                                 ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    DATE: 07/01/2525        TIME: 07:00 AM                  EMAILID: 0000 0000 0000 0000 0000           ///
///                                                                                                        ///
///    UNREAD: [X]             READ: [ ]                                                                   ///
///                                                                                                        ///
///    SENDER:                                                                                             ///
///        STONEDUFODUDE@WEACEDGAMES.COM                                                                   ///
///                                                                                                        ///
///    RECIPIENT:                                                                                          ///
///        EXECUTIVE@WEACEDGAMES.COM                                                                       ///
///                                                                                                        ///
///    SUBJECT:                                                                                            ///
///        LET ME GET THIS STRAIGHT!?!?                                                                    ///
///                                                                                                        ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                    ---BODY OF COMPANY TRANSMISSION---                                  ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    MESSAGE:                                                                                            ///
///        LOOK HERE MOTHERFUCKER                                                                          ///
///            FIRST... YOU CAME INTO THE INTERVIEW LOOKING LIKE A FUCKING GHOST                           ///
///            BITCH YOU GOT THEM THICK ASS GLASSES, WITH THE BIG ASS NOSE                                 ///
///            TO SUPPORT IT                                                                               ///
///                                                                                                        ///
///            TRANSLATION MOTHERFUCKER NEVER LEFT HIS HOUSE SINCE THE 4TH GRADE                           ///
///                                                                                                        ///
///            THE COMPUTER...                                                                             ///
///            HAS BEEN YOUR ONLY FRIEND, ONLY GIRLFRIEND, AND ONLY WIFE.                                  ///
///            YOU WILL DIE AND WILL BE BURIED WITH MOTHERFUCKER                                           ///
///            YOU'LL DO JUST FINE                                                                         ///
///                                                                                                        ///
///            YO NERDY ASS, IS REALLY GONNA STAND HERE AND ACT LIKE NO ONE HAS HIM FIGURED                ///
///            LMAO!!!                                                                                     ///
///                                                                                                        ///
///            SECCOND, I GOT YOU CHEAP DIDNT I???                                                         ///
///            DONT HATE THE FISHERMAN, HATE THE BAIT                                                      ///
///                                                                                                        ///
///                                                                                                        ///
///    SINGNATURE:                                                                                         ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                                                                                        ///
///    SOURCE:                                                                                             ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///    DESTINATION:                                                                                        ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///                                    ---END OF COMPANY TRANSMISSION---                                   ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
///                                    ---START OF COMPANY TRANSMISSION---                                 ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    DATE: 07/01/2525        TIME: 07:00 AM                  EMAILID: 0000 0000 0000 0000 0000           ///
///                                                                                                        ///
///    UNREAD: [X]             READ: [ ]                                                                   ///
///                                                                                                        ///
///    SENDER:                                                                                             ///
///        STONEDUFODUDE@WEACEDGAMES.COM                                                                   ///
///                                                                                                        ///
///    RECIPIENT:                                                                                          ///
///        EXECUTIVE@WEACEDGAMES.COM                                                                       ///
///                                                                                                        ///
///    SUBJECT:                                                                                            ///
///        LET ME GET THIS STRAIGHT!?!?                                                                    ///
///                                                                                                        ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                    ---BODY OF COMPANY TRANSMISSION---                                  ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    MESSAGE:                                                                                            ///
///        PROGRAMMER,                                                                                     ///
///            I AM GOING TO NEED YOU TO SUBMIT REPORTS ON PROGRESS YOU MADE SO FAR WITH THE               ///
///            GAME ENGINE, BY THE WAY WHAT IS THE PRODUCT CALLED?                                         ///
///                                                                                                        ///
///                                                                                                        ///
///    SINGNATURE:                                                                                         ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                                                                                        ///
///    SOURCE:                                                                                             ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///    DESTINATION:                                                                                        ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///                                    ---END OF COMPANY TRANSMISSION---                                   ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
///                                    ---START OF COMPANY TRANSMISSION---                                 ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    DATE: 07/01/2525        TIME: 07:00 AM                  EMAILID: 0000 0000 0000 0000 0000           ///
///                                                                                                        ///
///    UNREAD: [X]             READ: [ ]                                                                   ///
///                                                                                                        ///
///    SENDER:                                                                                             ///
///        STONEDUFODUDE@WEACEDGAMES.COM                                                                   ///
///                                                                                                        ///
///    RECIPIENT:                                                                                          ///
///        EXECUTIVE@WEACEDGAMES.COM                                                                       ///
///                                                                                                        ///
///    SUBJECT:                                                                                            ///
///        LET ME GET THIS STRAIGHT!?!?                                                                    ///
///                                                                                                        ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                    ---BODY OF COMPANY TRANSMISSION---                                  ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    MESSAGE:                                                                                            ///
///        THE SUMMER OFFERS ME TO SAY HELLO TO MY FELLOW MAN,                                             ///
///            ITS A HONOR TO SERVE WITH YOU AS YOUR HONARY ART DIRECTOR, BRINGING OUT YOUR                ///
///            INNER INSPIRATION. TRULY A MARVELOUS DAY INDEED                                             ///
///                                                                                                        ///
///        YOUR INSPIRATION,                                                                               ///
///            THE ART PERSON                                                                              ///
///                                                                                                        ///
///                                                                                                        ///
///    SINGNATURE:                                                                                         ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                                                                                        ///
///    SOURCE:                                                                                             ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///    DESTINATION:                                                                                        ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///                                    ---END OF COMPANY TRANSMISSION---                                   ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
///                                    ---START OF COMPANY TRANSMISSION---                                 ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    DATE: 07/01/2525        TIME: 07:00 AM                  EMAILID: 0000 0000 0000 0000 0000           ///
///                                                                                                        ///
///    UNREAD: [X]             READ: [ ]                                                                   ///
///                                                                                                        ///
///    SENDER:                                                                                             ///
///        STONEDUFODUDE@WEACEDGAMES.COM                                                                   ///
///                                                                                                        ///
///    RECIPIENT:                                                                                          ///
///        EXECUTIVE@WEACEDGAMES.COM                                                                       ///
///                                                                                                        ///
///    SUBJECT:                                                                                            ///
///        LET ME GET THIS STRAIGHT!?!?                                                                    ///
///                                                                                                        ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                    ---BODY OF COMPANY TRANSMISSION---                                  ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    MESSAGE:                                                                                            ///
///         WHO THE FUCK IS THIS???                                                                        ///
///         I HATE YOU, GO FUCK YOURSELF AND GO AWAY                                                       ///
///                                                                                                        ///
///                                                                                                        ///
///    SINGNATURE:                                                                                         ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                                                                                        ///
///    SOURCE:                                                                                             ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///    DESTINATION:                                                                                        ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///                                    ---END OF COMPANY TRANSMISSION---                                   ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
///                                    ---START OF COMPANY TRANSMISSION---                                 ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    DATE: 07/01/2525        TIME: 07:00 AM                  EMAILID: 0000 0000 0000 0000 0000           ///
///                                                                                                        ///
///    UNREAD: [X]             READ: [ ]                                                                   ///
///                                                                                                        ///
///    SENDER:                                                                                             ///
///        STONEDUFODUDE@WEACEDGAMES.COM                                                                   ///
///                                                                                                        ///
///    RECIPIENT:                                                                                          ///
///        EXECUTIVE@WEACEDGAMES.COM                                                                       ///
///                                                                                                        ///
///    SUBJECT:                                                                                            ///
///        LET ME GET THIS STRAIGHT!?!?                                                                    ///
///                                                                                                        ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                    ---BODY OF COMPANY TRANSMISSION---                                  ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    MESSAGE:                                                                                            ///
///        YOUR PROGRAMMER ART IS DONKEY SHIT, SHALL I ELLABORATE ???                                      ///
///        DO YOU ALWAYS HAVE TO BE AN ASSHOLE?                                                            ///
///                                                                                                        ///
///                                                                                                        ///
///    SINGNATURE:                                                                                         ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                                                                                        ///
///    SOURCE:                                                                                             ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///    DESTINATION:                                                                                        ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///                                    ---END OF COMPANY TRANSMISSION---                                   ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
///                                    ---START OF COMPANY TRANSMISSION---                                 ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    DATE: 07/01/2525        TIME: 07:00 AM                  EMAILID: 0000 0000 0000 0000 0000           ///
///                                                                                                        ///
///    UNREAD: [X]             READ: [ ]                                                                   ///
///                                                                                                        ///
///    SENDER:                                                                                             ///
///        STONEDUFODUDE@WEACEDGAMES.COM                                                                   ///
///                                                                                                        ///
///    RECIPIENT:                                                                                          ///
///        EXECUTIVE@WEACEDGAMES.COM                                                                       ///
///                                                                                                        ///
///    SUBJECT:                                                                                            ///
///        LET ME GET THIS STRAIGHT!?!?                                                                    ///
///                                                                                                        ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                    ---BODY OF COMPANY TRANSMISSION---                                  ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///                                                                                                        ///
///    MESSAGE:                                                                                            ///
///        WHAZZ UPPPPPP!!!,                                                                               ///
///            HAPPY HOLIDAYS!!! WELCOME TO TASK 37, TODAYS GOAL IS CONTINUE                               ///
///            LAST TASK CURRENTLY THE ENGINE USES A TEXT FILE FOR LOADING ENTITY AND CONFIG               ///
///            FILES, THIS IS VERY LIMITING. I WANT TO LOAD COMPLEX DATA STRUCTURES. CURRENTLY             ///
///            FOR CLASSES I HAVE CLASS AND SUBCLASS. I NEED A DATA STUCTURE THATS SIMPLE AND              ///
///            CAN SUPPORT COMPLEX STRUCTURES. JSON! ITS PLAIN TEXT, COMMON, AND MORE.                     ///
///            THIS WILL SOLVE ALL LOT THE ISSUES OF CREATING A PLAYER STRUCTURE, THE GOAL IS              ///
///            TO MAKE IT MORE DATA DRIVEN AND AVOID HARD CODING                                           ///
///                                                                                                        ///
///                                                                                                        ///
///        "GOAL 1"                                                                                        ///
///            IS TO CONVERT FROM THE CURRENT PLAIN TEXT FILE LOAD SYSTEM FOR ENTITIES AND                 ///
///            ASSET LOADING TO A JSON FILE SYSTEM                                                         ///
///                                                                                                        ///
///                                                                                                        ///
///        "GOAL 2"                                                                                        ///
///            FINALLY CHANGE SCENE_LOAD AND SCENE_SAVE TO SOMETHING THAT MAKES BETTER SENSE.              ///
///            SINCE IT HANDLES ENTITY FILES. IT SHOULD BE ENTITY_LOAD AND ENTITY_SAVE.                    ///
///            SO THATS THAT OPERATION OUTLINE XD                                                          ///
///                                                                                                        ///
///                                                                                                        ///
///    SINGNATURE:                                                                                         ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00             ///
///                                                                                                        ///
///                TEARLINE                                                        TEARLINE                ///
///--------------------------------------------------------------------------------------------------------///
///                TEARLINE                                                        TEARLINE                ///
///                                                                                                        ///
///    SOURCE:                                                                                             ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///    DESTINATION:                                                                                        ///
///        TERMINAL: LOCAL COMPUTER                                                                        ///
///        IP: 0000:000:0000:0000:0000:0000:0000:0000              PORT: 25                                ///
///        ADDRESS: WEACEDGAMES HEADQUARTERS , RUFFNECKS STATION                                           ///
///        PLANET: MOON                                                                                    ///
///                                                                                                        ///
///                                    ---END OF COMPANY TRANSMISSION---                                   ///
///                            ---WEACEDGAMES AUTHORIZED PERSONNEL EYES ONLY---                            ///
///                                    ---VIOLATORS WILL BE EXECUTED---                                    ///
///    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "scene_load.h"

std::vector<std::vector<std::string>> SceneLoad::loadEntities()
{
    std::vector<std::vector<std::string>> files;
    for (const auto& entry : std::filesystem::directory_iterator("./scene/entities"))
    {
        if(entry.is_regular_file())
        {   
            std::vector<std::string> file;
            std::ifstream file_read("./scene/entities/" + entry.path().filename().string());
            if(file_read.is_open())
            {
                std::string line;
                while(getline(file_read, line)){
                    file.push_back(line);
                }
                file_read.close();
            }
            else
            {
                std::cerr << "ERROR::ENTITIES::LOADING_ENTITY" << std::endl;
            }
            files.push_back(file);
        }
        else if(entry.is_directory())
        {
            for (const auto& subEntry : std::filesystem::directory_iterator("./scene/entities/" + entry.path().filename().string()) )
            {
                if(subEntry.is_regular_file())
                {
                    std::vector<std::string> file;
                    std::ifstream file_read("./scene/entities/" + entry.path().filename().string() + "/" + subEntry.path().filename().string());
                    
                    if(file_read.is_open())
                    {
                        std::string line;
                        while(getline(file_read, line))
                        {
                            file.push_back(line);
                        }
                        file_read.close();
                    }
                    else
                    {
                        std::cerr << "ERROR::CLASS::LOADING_ENTITY" << std::endl;
                    }
                    files.push_back(file);
                }
                else if(subEntry.is_directory())
                {
                    for (const auto& subSubEntry : std::filesystem::directory_iterator("./scene/entities/" + entry.path().filename().string() + "/" + subEntry.path().filename().string()))
                    {
                        std::vector<std::string> file;
                        std::ifstream file_read("./scene/entities/" + entry.path().filename().string() + "/" + subEntry.path().filename().string() + "/" + subSubEntry.path().filename().string());
                        
                        if(file_read.is_open())
                        {
                            std::string line;
                            while(getline(file_read, line))
                            {
                                file.push_back(line);
                            }
                            file_read.close();
                        }
                        else
                        {
                            std::cerr << "ERROR::SUBCLASS::LOADING_ENTITY" << std::endl;
                        }
                        files.push_back(file);
                    }
                }
            }
        }
    }
    return files;
};

std::vector<Entity*> SceneLoad::generateEntities(std::vector<std::vector<std::string>> files, std::vector<Shader*> loaded_shaders, std::vector<Model*> loaded_models, std::vector<Sprite*> loaded_sprites, std::vector<Geometry*> loaded_geometry, Camera* camera)
{
    std::vector<Entity*> entities;

    for(int index=0; index < files.size() ; index++)
    {

        std::string type = "";
        std::string name = "";
        std::string tag = "";

        std::string pathVertexShader = "";
        std::string pathFragmentShader = "";

        int shader_id = 0;
        int shader_boundingBox_id = -1;
        int model_id = 0;
        int sprite_id = 0;

        std::string pathImage = "";

        std::string geometryType = "";
        
        float colorRed = 0.0f;
        float colorGreen = 0.0f;
        float colorBlue = 0.0f;

        float xPos = 0.0f;
        float yPos = 0.0f;
        float zPos = 0.0f;

        float xScale = 0.0f;
        float yScale = 0.0f;
        float zScale = 0.0f;

        float xRotation = 0.0f;
        float yRotation = 0.0f;
        float zRotation = 0.0f;

        bool enableRender = false;
        bool enableBoundingBox = false;
        bool enableCollider = false;

        for(int subIndex=0; subIndex<files[index].size(); subIndex++)
        {
            size_t pos = files[index][subIndex].find('=');

            if(pos != std::string::npos)
            {
                std::string key = files[index][subIndex].substr(0, pos);
                std::string value = files[index][subIndex].substr(pos + 1);

                if(key=="TYPE")
                    type = value;
                if(key=="NAME")
                    name = value;
                if(key=="TAG")
                    tag = value;

                if(type=="camera")
                {
                    if(key=="POSITIONX")
                        xPos = std::stof(value);
                    if(key=="POSITIONY")
                        yPos = std::stof(value);
                    if(key=="POSITIONZ")
                        zPos = std::stof(value);
                }
                
                if(type=="model")
                {
                    if(key=="SHADERID")
                        shader_id = std::stoi(value);
                    if(key=="SHADERBOUNDINGBOXID")
                        shader_boundingBox_id = std::stoi(value);
                    if(key=="MODELID")
                        model_id = std::stoi(value);

                    if(key=="POSITIONX")
                        xPos = std::stof(value);
                    if(key=="POSITIONY")
                        yPos = std::stof(value);
                    if(key=="POSITIONZ")
                        zPos = std::stof(value);

                    if(key=="SCALEX")
                        xScale = std::stof(value);
                    if(key=="SCALEY")
                        yScale = std::stof(value);
                    if(key=="SCALEZ")
                        zScale = std::stof(value);

                    if(key=="ROTATIONX")
                        xRotation = std::stof(value);
                    if(key=="ROTATIONY")
                        yRotation = std::stof(value);
                    if(key=="ROTATIONZ")
                        zRotation = std::stof(value);

                    if(key=="ENABLERENDER")
                        enableRender = std::stoi(value);
                    if(key=="ENABLEBOUNDINGBOX")
                        enableBoundingBox = std::stoi(value);
                }

                if(type=="sprite")
                {
                    if(key=="SHADERID")
                        shader_id = std::stoi(value);
                    if(key=="SPRITEID")
                        sprite_id = std::stoi(value);

                    if(key=="POSITIONX")
                        xPos = std::stof(value);
                    if(key=="POSITIONY")
                        yPos = std::stof(value);
                    if(key=="POSITIONZ")
                        zPos = std::stof(value);

                    if(key=="SCALEX")
                        xScale = std::stof(value);
                    if(key=="SCALEY")
                        yScale = std::stof(value);
                    if(key=="SCALEZ")
                        zScale = std::stof(value);

                    if(key=="ROTATIONX")
                        xRotation = std::stof(value);
                    if(key=="ROTATIONY")
                        yRotation = std::stof(value);
                    if(key=="ROTATIONZ")
                        zRotation = std::stof(value);

                    if(key=="ENABLERENDER")
                        enableRender = std::stoi(value);
                    if(key=="ENABLEBOUNDINGBOX")
                        enableBoundingBox = std::stoi(value);
                }

                if(type=="geometry")
                {
                    if(key=="SHADERID")
                        shader_id = std::stoi(value);
                    if(key=="SHADERBOUNDINGBOXID")
                        shader_boundingBox_id = std::stoi(value);
                    if(key=="MODELID")
                        model_id = std::stoi(value);

                    if(key=="POSITIONX")
                        xPos = std::stof(value);
                    if(key=="POSITIONY")
                        yPos = std::stof(value);
                    if(key=="POSITIONZ")
                        zPos = std::stof(value);

                    if(key=="GEOMETRYTYPE")
                        geometryType = value;
                    if(key=="GEOMETRYCOLORRED")
                        colorRed = std::stof(value);
                    if(key=="GEOMETRYCOLORGREEN")
                        colorGreen = std::stof(value);
                    if(key=="GEOMETRYCOLORBLUE")
                        colorBlue = std::stof(value);

                    if(key=="SCALEX")
                        xScale = std::stof(value);
                    if(key=="SCALEY")
                        yScale = std::stof(value);
                    if(key=="SCALEZ")
                        zScale = std::stof(value);

                    if(key=="ROTATIONX")
                        xRotation = std::stof(value);
                    if(key=="ROTATIONY")
                        yRotation = std::stof(value);
                    if(key=="ROTATIONZ")
                        zRotation = std::stof(value);

                    if(key=="ENABLERENDER")
                        enableRender = std::stoi(value);
                    if(key=="ENABLEBOUNDINGBOX")
                        enableBoundingBox = std::stoi(value);
                    if(key=="ENABLECOLLIDER")
                        enableCollider = std::stoi(value);
                }

                if(type=="overlay")
                {

                    if(key=="SHADERID")
                        shader_id = std::stoi(value);
                    if(key=="SHADERBOUNDINGBOXID")
                        shader_boundingBox_id = std::stoi(value);
                    if(key=="MODELID")
                        model_id = std::stoi(value);


                    if(key=="POSITIONX")
                        xPos = std::stof(value);
                    if(key=="POSITIONY")
                        yPos = std::stof(value);
                    if(key=="POSITIONZ")
                        zPos = std::stof(value);

                    if(key=="SCALEX")
                        xScale = std::stof(value);
                    if(key=="SCALEY")
                        yScale = std::stof(value);
                    if(key=="SCALEZ")
                        zScale = std::stof(value);

                    if(key=="ROTATIONX")
                        xRotation = std::stof(value);
                    if(key=="ROTATIONY")
                        yRotation = std::stof(value);
                    if(key=="ROTATIONZ")
                        zRotation = std::stof(value);

                    if(key=="ENABLERENDER")
                        enableRender = std::stoi(value);
                    if(key=="ENABLEBOUNDINGBOX")
                        enableBoundingBox = std::stoi(value);
                }
                
            }
        }

        Entity* tempEntity = new Entity();

        if(type=="camera")
        {
            tempEntity->setCamera(camera);
            tempEntity->setName(name);
            tempEntity->setTag(tag);
            tempEntity->setType(type);
            tempEntity->setPosition(glm::vec3(xPos, yPos, zPos));
            entities.push_back(tempEntity);
        }

        if(type=="model")
        {
            for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
            {
                if(shader_id == loaded_shaders[subIndex]->assetShaderId)
                    tempEntity->setShader(loaded_shaders[subIndex]);
            }

            if(shader_boundingBox_id != -1)
            {
                for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
                {
                    if(shader_boundingBox_id == loaded_shaders[subIndex]->assetShaderId)
                        tempEntity->setShaderBoundingBox(loaded_shaders[subIndex]);
                }
            }

            for(int subIndex=0; subIndex<loaded_models.size(); subIndex++)
            {
                if(model_id == loaded_models[subIndex]->assetModelID)
                    tempEntity->setModel(loaded_models[subIndex]);

            }

            tempEntity->setName(name);
            tempEntity->setTag(tag);
            tempEntity->setType(type);
            tempEntity->setPosition(glm::vec3(xPos, yPos, zPos));
            tempEntity->setScale(glm::vec3(xScale, yScale, zScale));
            tempEntity->setRotation(glm::vec3( xRotation, yRotation, zRotation));
            tempEntity->setEnableRender(enableRender);
            tempEntity->setEnableBoundingBox(enableBoundingBox);
            entities.push_back(tempEntity);
        }

        



        if(type=="sprite")
        {
            for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
            {
                if(shader_id == loaded_shaders[subIndex]->assetShaderId)
                    tempEntity->setShader(loaded_shaders[subIndex]);
            }

            for(int subIndex=0; subIndex<loaded_sprites.size(); subIndex++)
            {
                if(sprite_id == loaded_sprites[subIndex]->assetSpriteID)
                {
                    tempEntity->setSprite(loaded_sprites[subIndex]);
                }
            }

            tempEntity->setName(name);
            tempEntity->setTag(tag);
            tempEntity->setType(type);
            tempEntity->setPosition(glm::vec3(xPos, yPos, zPos));
            tempEntity->setScale(glm::vec3(xScale, yScale, zScale));
            tempEntity->setRotation(glm::vec3( xRotation, yRotation, zRotation));
            tempEntity->setEnableRender(enableRender);
            tempEntity->setEnableBoundingBox(enableBoundingBox);
            entities.push_back(tempEntity);
        }



        if(type=="overlay")
        {
            for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
            {
                if(shader_id == loaded_shaders[subIndex]->assetShaderId)
                    tempEntity->setShader(loaded_shaders[subIndex]);
            }

            if(shader_boundingBox_id != -1)
            {
                for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
                {
                    if(shader_boundingBox_id == loaded_shaders[subIndex]->assetShaderId)
                        tempEntity->setShaderBoundingBox(loaded_shaders[subIndex]);
                }
            }

            for(int subIndex=0; subIndex<loaded_models.size(); subIndex++)
            {
                if(model_id == loaded_models[subIndex]->assetModelID)
                    tempEntity->setModel(loaded_models[subIndex]);

            }
            tempEntity->setName(name);
            tempEntity->setTag(tag);
            tempEntity->setType(type);
            tempEntity->setPosition(glm::vec3(xPos, yPos, zPos));
            tempEntity->setScale(glm::vec3(xScale, yScale, zScale));
            tempEntity->setRotation(glm::vec3( xRotation, yRotation, zRotation));
            tempEntity->setEnableRender(enableRender);
            tempEntity->setEnableBoundingBox(enableBoundingBox);
            entities.push_back(tempEntity);
        }

        if(type=="geometry")
        {
            for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
            {
                if(shader_id == loaded_shaders[subIndex]->assetShaderId)
                    tempEntity->setShader(loaded_shaders[subIndex]);
            }

            if(shader_boundingBox_id != -1)
            {
                for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
                {
                    if(shader_boundingBox_id == loaded_shaders[subIndex]->assetShaderId)
                        tempEntity->setShaderBoundingBox(loaded_shaders[subIndex]);
                }
            }
            
            tempEntity->setGeometry(loaded_geometry[0]);
            tempEntity->setName(name);
            tempEntity->setTag(tag);
            tempEntity->setType(type);
            tempEntity->setPosition(glm::vec3(xPos, yPos, zPos));
            tempEntity->setScale(glm::vec3(xScale, yScale, zScale));
            tempEntity->setRotation(glm::vec3( xRotation, yRotation, zRotation));
            tempEntity->setEnableRender(enableRender);
            tempEntity->setEnableBoundingBox(enableBoundingBox);
            tempEntity->setEnableCollider(enableCollider);
            tempEntity->setColor( glm::vec3( colorRed, colorGreen, colorBlue) );
            entities.push_back(tempEntity);
        }
    }
    return entities;
};