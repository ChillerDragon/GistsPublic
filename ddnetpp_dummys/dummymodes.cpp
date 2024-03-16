if (m_pPlayer->m_DummyMode == 0)
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;


			//Selfkills
			if (isFreezed)
			{
				//wenn der bot freeze is warte erstmal n paar sekunden und dann kill dich
				if (Server()->Tick() % 300 == 0)
				{
					//Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}
			}




			char aBuf[256];
			//str_format(aBuf, sizeof(aBuf), "speed:  x: %f y: %f", m_Core.m_Vel.x, m_Core.m_Vel.y);
			//str_format(aBuf, sizeof(aBuf), "target:  x: %d y: %d", m_Input.m_TargetX, m_Input.m_TargetY);
			str_format(aBuf, sizeof(aBuf), "pos.x %.2f pos.y %.2f", m_Core.m_Pos.x, m_Core.m_Pos.y);
			//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);

			if (1 == 2) //just for debuggin
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
					m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
				}
			}
			else //normal
			{
				float Angle = m_AngleTo;

				if (Server()->Tick() > m_AngleTickStart + m_AngleTickTime)
				{
					if (Server()->Tick() >= m_AngleTickNext)
					{
						m_AngleFrom = m_AngleTo;

						m_AngleTo += (rand() % 360) - 180;
						m_AngleTickTime = Server()->TickSpeed() / 2 + (rand() % (Server()->TickSpeed() / 2));

						m_AngleTickStart = Server()->Tick();
						m_AngleTickNext = m_AngleTickStart + m_AngleTickTime + Server()->TickSpeed() * 2 + Server()->TickSpeed() / 2 * (rand() % 10);

						// wann sollen die emotes gemacht werden? oder willst du das nachher machen? bei dem default mode is alles random bei dem anderen sollte es gefühle usw geben hier nich
						// pChr->m_EmoteType = EMOTE_HAPPY; 
						// pChr->m_EmoteStop = Server()->Tick() + Server()->TickSpeed(); // = emote bleibt eine sekunde
						// tja, dachte das wär hier drin. schade
					}
				}
				else
				{
					Angle = m_AngleFrom + (m_AngleTo - m_AngleFrom) * (Server()->Tick() - m_AngleTickStart) / m_AngleTickTime;
				}

				float AngleRad = Angle * pi / 180.f;
				m_Input.m_TargetX = cosf(AngleRad) * 100;
				m_Input.m_TargetY = sinf(AngleRad) * 100;
			}
		





			// wenn targetX > 0 ist, guckt er nach rechts. bei < 0 halt nach links
			// bei targetY ist es so, wenn das > 0 ist guckt er nach UNTEN. bei < 0 nach OBEN

			// ok alles schön und gut aber wie lass ich den jetzt moven? also die augen nicht springen sondern bewegen

			// m_Input.m_TargetX = 1;
			// m_Input.m_TargetY = 0; // so guckt er halt z.B. nach rechts. da kannste jetzt mit rumrechnen (lass da pls) [steht doch oben ._.] egal

			// wenn du was mit der zeit rechnen willst, nimm den server tick. Server()->Tick() und Server()->TickSpeed() [das sollte eigentlich immer 50 sein]

			// m_Input.m_TargetX = Server()->Tick() % Server()->TickSpeed; // würde z.B. machen, dass m_TargetX zwischen 0 und 49 liegt (rechnet ja Modulo 50). nur so als beispiel. bringt in dem fall jetzt wenig

			//float Angle = (float)Server()->Tick(); // teste mal
			//float Angle = Server()->Tick() / (float)Server()->TickSpeed() * 360; // player dreht sich jede sekunde einmal
			//float Angle = (float)Server()->Tick() / (float)Server()->TickSpeed() * 720.f; // player dreht sich jede sekunde zwei mal (720 = 360*2)schon kla skype

			//float AngleRad = Angle * pi / 180.f;
			//m_Input.m_TargetX = cosf(AngleRad) * 100;
			//m_Input.m_TargetY = sinf(AngleRad) * 100; // probier das mal aus. sollte sich eigentlich alle 2 sekunden einmal komplett gedreht haben. (bin etwas müde ._.) :c

			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();
				int r = rand() % 100;
				GameServer()->SendEmoticon(m_pPlayer->GetCID(), r < 10 ? 5 : r < 55 ? 2 : 7);

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() * 10 + Server()->TickSpeed() * (rand() % 21);
			}
		}
		else if (m_pPlayer->m_DummyMode == 1) 
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 1;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = -1;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;


			//bouncy moves
			/*
			if (m_Input.m_Direction == -1)
			{
				m_Input.m_Direction = 1;
			}
			else
			{
				m_Input.m_Direction = -1;
			}

			*/

			//pikus aimpot!
			CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
			if (pChr && pChr->IsAlive())
			{
				m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
			}


			m_Input.m_Jump = 1;



			



			//emotes
			
			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();
				int r = rand() % 100;
				GameServer()->SendEmoticon(m_pPlayer->GetCID(), r < 10 ? 5 : r < 55 ? 2 : 7);

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() * 10 + Server()->TickSpeed() * (rand() % 21);
			}
		}
		else if (m_pPlayer->m_DummyMode == 2)
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 1;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;


			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();


	

				GameServer()->SendEmoticon(m_pPlayer->GetCID(),2);

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() / 5 + Server()->TickSpeed() * (rand() % 3);
			}
			else
			{

				if (m_Input.m_Fire == 0)
				{
					m_Input.m_Fire++;
				}
				else
				{
					m_Input.m_Fire = 0;
				}


				//pikus aimpot!
				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
				}



				m_Input.m_Jump = 1;




	

				if (m_Input.m_Hook == 0)
				{
					m_Input.m_Hook = 1;
				}
				else
				{
					m_Input.m_Hook = 0;
				}
			}

		}
		else if (m_pPlayer->m_DummyMode == 3)
		{
			//rest dummy (zuruecksetzten)
			//m_Input.m_Hook = 0;
			//m_Input.m_Jump = 0;
			//m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;



			//m_Core.m_ActiveWeapon = WEAPON_HAMMER;







			//happy finish
			if (m_DummyFinished == true)
			{
				if (m_DummyFinishes == 1)
				{
					m_DummyShowRank = true;
					m_Input.m_Jump = 1;
					m_Input.m_Jump = 0;
					m_Input.m_Jump = 1;
					m_Input.m_Jump = 0;
					GameServer()->SendEmoticon(m_pPlayer->GetCID(), 3);
					GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "GoodGame :) Thank you team for help'in me finish this hard map!");
					m_DummyFinished = false;
				}
				else if (m_DummyFinishes == 2)
				{
					GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "yay finished AGIAN!");
					m_DummyFinished = false;
					
				}
				else
				{
					GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "gg :)");
					m_DummyFinished = false;
				}
			}
			//showing rank
			if (m_DummyShowRank == true)
			{
				if (frandom() * 100 < 2)
				{
					GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "look at my cool rank!");
					GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "/rank");
					m_DummyShowRank = false;
				}
			}


			//weapon switch old
			/*
			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();
				//m_Core.m_ActiveWeapon = WEAPON_GUN;
				DoWeaponSwitch();

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() / 10 + Server()->TickSpeed() * (rand() % 21);
			}
			else
			{
				m_Core.m_ActiveWeapon = WEAPON_HAMMER;
			}
			*/

			


			//emotes fast
			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();


				int r = rand() % 100;
				GameServer()->SendEmoticon(m_pPlayer->GetCID(), r < 10 ? 5 : r < 55 ? 2 : 7);

				m_DummyHammer ^= true;

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() / 6;
			}


			//weapons
			if (m_FreezeTime == 0)
			{
				if (m_DummyHammer) //bubub
				{
					//m_Core.m_ActiveWeapon = WEAPON_HAMMER;
					SetWeapon(0);
				}
				else
				{
					SetWeapon(1);
					//m_Core.m_ActiveWeapon = WEAPON_GUN;
				}
			}

			// moving eyes

			float Angle = m_AngleTo;

			// überprüfen ob die animation schon vorbei ist (also um z.B. 90° schon gedreht wurde)
			if (Server()->Tick() > m_AngleTickStart + m_AngleTickTime)
			{
				// danach überprüfen, ob es auch schon zeit ist, um die nächste animation zu starten
				if (Server()->Tick() >= m_AngleTickNext)
				{
					m_AngleFrom = m_AngleTo; // erst mal die startrotation auf die vorherige endrotation setzen

					m_AngleTo += (rand() % 360) - 180; // dann die neue endrotation setzen (= die vorherige rotation + irgendeine zufällige zahl zwischen -180 und + 180)
					m_AngleTickTime = Server()->TickSpeed() / 15 + (rand() % (Server()->TickSpeed() / 15)); // wie lange die animation geht, hier also eine halbe sekunde + 

					m_AngleTickStart = Server()->Tick() / 10; // startzeit für die nächste animation setzen
					m_AngleTickNext = m_AngleTickStart + m_AngleTickTime + Server()->TickSpeed() * 2 + Server()->TickSpeed() / 2 * (rand() % 10);


					//jup alles ganz gut erkärt auch halbwegs verstanden aber selber umwenden hmmmm


					// wann sollen die emotes gemacht werden? oder willst du das nachher machen? bei dem default mode is alles random bei dem anderen sollte es gefühle usw geben hier nich
					// pChr->m_EmoteType = EMOTE_HAPPY; 
					// pChr->m_EmoteStop = Server()->Tick() + Server()->TickSpeed(); // = emote bleibt eine sekunde
					// tja, dachte das wär hier drin. schade
				}
			}
			else
			{
				// wenn die animation noch nicht vorbei ist, dann wird die rotation entsprechend auf einen wert zwischen z.B. 0° und 90° (also start und endrotation) gesetzt
				Angle = m_AngleFrom + (m_AngleTo - m_AngleFrom) * (Server()->Tick() - m_AngleTickStart) / m_AngleTickTime;
			}

			float AngleRad = Angle * pi / 180.f;
			m_Input.m_TargetX = cosf(AngleRad) * 100;
			m_Input.m_TargetY = sinf(AngleRad) * 100;

			//moving eyes end

			//shot schiessen schissen
			//im freeze nicht schiessen
			if (m_FreezeTime == 0)
			{
				m_LatestInput.m_TargetX = cosf(AngleRad) * 100;
				m_LatestInput.m_TargetY = sinf(AngleRad) * 100;
				m_LatestInput.m_Fire++;
				m_Input.m_Fire++;
				//FireWeapon(true);
				//m_Input.m_Jump = 1;
			}


			//hooken
			if (m_Core.m_HookState == HOOK_FLYING)
				m_Input.m_Hook = 1;
			else if (m_Core.m_HookState == HOOK_GRABBED)
			{
				if (frandom() * 250 < 1) //hmm hä xD ich will das er selten ganz lange hookt isses dass? sehr wsaelten. was stand da vorher
				{
					if (frandom() * 250 == 1)
						m_Input.m_Hook = 0;
					else
						m_Input.m_Hook = 1;
				}
				else
				{
					if (frandom() * 250 < 1)
						m_Input.m_Hook = 0;
					else
						m_Input.m_Hook = 1;
				}
			}
			else
			{
				if (frandom() * 250 < 3)
				{
					m_Input.m_Hook = 1;
				}
				else
					m_Input.m_Hook = 0;
			}

			//laufen (move xD)
			if (m_StopMoveTick && Server()->Tick() >= m_StopMoveTick)
			{
				m_LastMoveDirection = m_Input.m_Direction;
				m_Input.m_Direction = 0;
				m_StopMoveTick = 0;
			}
			if (Server()->Tick() >= m_MoveTick)
			{
				int Direction = rand() % 6;
				if (m_LastMoveDirection == -1)
				{
					if (Direction < 2)
						m_Input.m_Direction = 1;
					else
						m_Input.m_Direction = -1;
				}
				else
				{
					if (Direction < 2)
						m_Input.m_Direction = -1;
					else
						m_Input.m_Direction = 1;
				}
				m_StopMoveTick = Server()->Tick() + Server()->TickSpeed();
				m_MoveTick = Server()->Tick() + Server()->TickSpeed() * 3 + Server()->TickSpeed() * (rand() % 6);
			}
		}
		else if (m_pPlayer->m_DummyMode == 4) //mode 3 + selfkill
		{
			//rest dummy (zuruecksetzten)
			//m_Input.m_Hook = 0;
			//m_Input.m_Jump = 0;
			//m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;



			//m_Core.m_ActiveWeapon = WEAPON_HAMMER;
			SetWeapon(0);



			//freeze selfkilll

			if (m_DummyFreezed)
			{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					m_DummyFreezed = false;
			}


			//weapon switch
			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();
				//m_Core.m_ActiveWeapon = WEAPON_GUN;
				//DoWeaponSwitch();

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() / 10 + Server()->TickSpeed() * (rand() % 21);
			}
			else
			{
				//m_Core.m_ActiveWeapon = WEAPON_HAMMER;
				SetWeapon(0);
			}






			//emotes

			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();
				int r = rand() % 100;
				GameServer()->SendEmoticon(m_pPlayer->GetCID(), r < 10 ? 5 : r < 55 ? 2 : 7);

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() * 5 + Server()->TickSpeed() * (rand() % 21);
			}

			// moving eyes

			float Angle = m_AngleTo;

			// überprüfen ob die animation schon vorbei ist (also um z.B. 90° schon gedreht wurde)
			if (Server()->Tick() > m_AngleTickStart + m_AngleTickTime)
			{
				// danach überprüfen, ob es auch schon zeit ist, um die nächste animation zu starten
				if (Server()->Tick() >= m_AngleTickNext)
				{
					m_AngleFrom = m_AngleTo; // erst mal die startrotation auf die vorherige endrotation setzen

					m_AngleTo += (rand() % 360) - 180; // dann die neue endrotation setzen (= die vorherige rotation + irgendeine zufällige zahl zwischen -180 und + 180)
					m_AngleTickTime = Server()->TickSpeed() / 15 + (rand() % (Server()->TickSpeed() / 15)); // wie lange die animation geht, hier also eine halbe sekunde + 

					m_AngleTickStart = Server()->Tick() / 10; // startzeit für die nächste animation setzen
					m_AngleTickNext = m_AngleTickStart + m_AngleTickTime + Server()->TickSpeed() * 2 + Server()->TickSpeed() / 2 * (rand() % 10);


					//jup alles ganz gut erkärt auch halbwegs verstanden aber selber umwenden hmmmm


					// wann sollen die emotes gemacht werden? oder willst du das nachher machen? bei dem default mode is alles random bei dem anderen sollte es gefühle usw geben hier nich
					// pChr->m_EmoteType = EMOTE_HAPPY; 
					// pChr->m_EmoteStop = Server()->Tick() + Server()->TickSpeed(); // = emote bleibt eine sekunde
					// tja, dachte das wär hier drin. schade
				}
			}
			else
			{
				// wenn die animation noch nicht vorbei ist, dann wird die rotation entsprechend auf einen wert zwischen z.B. 0° und 90° (also start und endrotation) gesetzt
				Angle = m_AngleFrom + (m_AngleTo - m_AngleFrom) * (Server()->Tick() - m_AngleTickStart) / m_AngleTickTime;
			}

			float AngleRad = Angle * pi / 180.f;
			m_Input.m_TargetX = cosf(AngleRad) * 100;
			m_Input.m_TargetY = sinf(AngleRad) * 100;

			//moving eyes end

			//shot schiessen schissen
			if (frandom() * 25 < 3)// probier mal jetzt ob sich was ändert

			{
				m_LatestInput.m_TargetX = cosf(AngleRad) * 100;
				m_LatestInput.m_TargetY = sinf(AngleRad) * 100;
				m_LatestInput.m_Fire++;
				m_Input.m_Fire++;
				//FireWeapon(true);
				//m_Input.m_Jump = 1;
			}


			//hooken
			if (m_Core.m_HookState == HOOK_FLYING)
				m_Input.m_Hook = 1;
			else if (m_Core.m_HookState == HOOK_GRABBED)
			{
				if (frandom() * 250 < 1) //hmm hä xD ich will das er selten ganz lange hookt isses dass? sehr wsaelten. was stand da vorher
				{
					if (frandom() * 250 == 1)
						m_Input.m_Hook = 0;
					else
						m_Input.m_Hook = 1;
				}
				else
				{
					if (frandom() * 250 < 1)
						m_Input.m_Hook = 0;
					else
						m_Input.m_Hook = 1;
				}
			}
			else
			{
				if (frandom() * 250 < 3)
				{
					m_Input.m_Hook = 1;
				}
				else
					m_Input.m_Hook = 0;
			}

			//laufen (move xD)
			if (m_StopMoveTick && Server()->Tick() >= m_StopMoveTick)
			{
				m_LastMoveDirection = m_Input.m_Direction;
				m_Input.m_Direction = 0;
				m_StopMoveTick = 0;
			}
			if (Server()->Tick() >= m_MoveTick)
			{
				int Direction = rand() % 6;
				if (m_LastMoveDirection == -1)
				{
					if (Direction < 2)
						m_Input.m_Direction = 1;
					else
						m_Input.m_Direction = -1;
				}
				else
				{
					if (Direction < 2)
						m_Input.m_Direction = -1;
					else
						m_Input.m_Direction = 1;
				}
				m_StopMoveTick = Server()->Tick() + Server()->TickSpeed();
				m_MoveTick = Server()->Tick() + Server()->TickSpeed() * 3 + Server()->TickSpeed() * (rand() % 6);
			}
		}
		else if (m_pPlayer->m_DummyMode == 5) //hammerfly mode (taxi)
		{
			//m_Core.m_ActiveWeapon = WEAPON_HAMMER;
			m_Input.m_Direction = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Hook = 0;


			//taxi holen
			if (m_taxi)
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
				m_taxi = false;
			}

			//hook 5
			
			if (Server()->Tick() >= m_HookTickNext)
			{


				if (m_Core.m_HookState == HOOK_FLYING)
					m_Input.m_Hook = 1;
				else if (m_Core.m_HookState == HOOK_GRABBED)
					if (frandom() * 250 < 1) //hmm hä xD ich will das er selten ganz lange hookt isses dass? sehr wsaelten. was stand da vorher
					{
						if (frandom() * 250 == 1)
							m_Input.m_Hook = 0;
						else
							m_Input.m_Hook = 1;
					}
					else
					{
						m_Input.m_Hook = 0;
					}
				else
				{
					m_Input.m_Hook = 0;
				}
				

				m_HookTickNext = Server()->Tick() + Server()->TickSpeed() / 10;
			}

			

			//emote
			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();




				int r = rand() % 100;
				GameServer()->SendEmoticon(m_pPlayer->GetCID(), r < 10 ? 5 : r < 55 ? 2 : 7);

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() / 10;
			}

		}
		else if (m_pPlayer->m_DummyMode == 6) //selfkiller
		{

			//selfkill freeze
			//delay berechnung
			int r = rand() % 10000;

			if (m_DummyFreezed)
			{

				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
				}
				
				if (r <= 1)
				{
					GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "help me!");
				}
				else if (r == 2)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					m_DummyFreezed = false;
				}
				else if (r > 9990)
				{
					GameServer()->SendEmoticon(m_pPlayer->GetCID(), 3);
				}
				


			}
		}
		else if (m_pPlayer->m_DummyMode == 7)  //taxi
		{
			//m_Core.m_ActiveWeapon = WEAPON_HAMMER;
			SetWeapon(0);

			//pikus aimpot!
			CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
			if (pChr && pChr->IsAlive())
			{
				m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;


				//shot schiessen schissen
				//im freeze nicht schiessen
				if (m_DummyFreezed == false)
				{
					m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

					//schiess delay
					if (Server()->Tick() >= m_EmoteTickNext)
					{
						m_pPlayer->m_LastEmote = Server()->Tick();


						GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);

						m_LatestInput.m_Fire++;
						m_Input.m_Fire++;

						m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() / 2;
					}
					else
					{
						m_LatestInput.m_Fire = 0;
						m_Input.m_Fire = 0;
					}
					//FireWeapon(true);
					//m_Input.m_Jump = 1;
				}
				else if (m_DummyFreezed == true) //if (m_DummyFreezed == false)
				{
					m_LatestInput.m_Fire = 0;
					m_Input.m_Fire = 0;
					m_DummyFreezed = false;
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "hey im freezded lul xD");
				}
				else
				{
					GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "iwas is maechtig flasch gelaufen du bob");
				}

			}

			/*
			float Angle = m_AngleTo;

			float AngleRad = Angle * pi / 180.f;
			m_Input.m_TargetX = cosf(AngleRad) * 100;
			m_Input.m_TargetY = sinf(AngleRad) * 100;
			*/ 

		

			//emotes
			/*
			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();
				int r = rand() % 100;
				GameServer()->SendEmoticon(m_pPlayer->GetCID(), r < 10 ? 5 : r < 55 ? 2 : 7);

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() + Server()->TickSpeed() * (rand() % 4);
			}
			*/

		

		}
		else if (m_pPlayer->m_DummyMode == 8)  //testy emotions and much vars
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;




		}
		else if (m_pPlayer->m_DummyMode == 9)  //move left
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			m_Input.m_Direction = -1;
		}
		else if (m_pPlayer->m_DummyMode == 10)  //move right
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			m_Input.m_Direction = 1;
		}
		else if (m_pPlayer->m_DummyMode == 11)  //move Jump
		{

			char aBuf[256];
			str_format(aBuf, sizeof(aBuf), "speed:  x: %f y: %f", m_Core.m_Vel.x, m_Core.m_Vel.y);

			//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);

			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			m_Input.m_Jump = 1;
		}
		else if (m_pPlayer->m_DummyMode == 12)  //Damage dude
		{
			m_isDmg = true;

			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();
				int r = rand() % 100;
				GameServer()->SendEmoticon(m_pPlayer->GetCID(), r < 10 ? 5 : r < 55 ? 2 : 7);

				m_Input.m_Jump = 1;

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() + Server()->TickSpeed() * (rand() % 4);
			}
			else
			{
				m_Input.m_Jump = 0;
			}

			//laufen (move xD)
			if (m_StopMoveTick && Server()->Tick() >= m_StopMoveTick)
			{
				m_LastMoveDirection = m_Input.m_Direction;
				m_Input.m_Direction = 0;
				m_StopMoveTick = 0;
			}
			if (Server()->Tick() >= m_MoveTick)
			{
				int Direction = rand() % 6;
				if (m_LastMoveDirection == -1)
				{
					if (Direction < 2)
						m_Input.m_Direction = 1;
					else
						m_Input.m_Direction = -1;
				}
				else
				{
					if (Direction < 2)
						m_Input.m_Direction = -1;
					else
						m_Input.m_Direction = 1;
				}
				m_StopMoveTick = Server()->Tick() + Server()->TickSpeed() * 10 / Server()->TickSpeed() * (rand() % 60);
				m_MoveTick = Server()->Tick() + Server()->TickSpeed() * 3 + Server()->TickSpeed() * (rand() % 6);
			}

		}
		else if (m_pPlayer->m_DummyMode == 13)  // fly bot
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			m_Input.m_TargetX = 0;
			m_Input.m_TargetY = -1;
			m_LatestInput.m_TargetX = 0;
			m_LatestInput.m_TargetY = -1;


			if (m_Core.m_Vel.y > 0)
			{
				m_Input.m_Hook = 1;
			}
			else
			{
				m_Input.m_Hook = 0;
			}

		}
		else if (m_pPlayer->m_DummyMode == 14)  // fly bot left
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = -1;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			m_Input.m_TargetX = 0;
			m_Input.m_TargetY = -1;



			if (m_Core.m_Vel.y > 0)
			{
				m_Input.m_Hook = 1;
			}
			else
			{
				m_Input.m_Hook = 0;
			}

		}
		else if (m_pPlayer->m_DummyMode == 15)  // fly bot right
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 1;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			m_Input.m_TargetX = 0;
			m_Input.m_TargetY = -1;



			if (m_Core.m_Vel.y > 0)
			{
				m_Input.m_Hook = 1;
			}
			else
			{
				m_Input.m_Hook = 0;
			}

		}
		else if (m_pPlayer->m_DummyMode == 16)  // blocker (better ki)
		{
			//rest dummy (zuruecksetzten)
			//m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			if (m_Core.m_Vel.y > 1) // "vel < 1" beim hochfliegen main   "vel > 1" beim fallen main
			{
				m_Input.m_Direction = 1;

				//emotes & jump
				if (Server()->Tick() >= m_EmoteTickNextFast)
				{
					m_pPlayer->m_LastEmote = Server()->Tick();
					int r = rand() % 100;
					GameServer()->SendEmoticon(m_pPlayer->GetCID(), r < 10 ? 5 : r < 55 ? 2 : 7);
					m_Input.m_Jump = 1;



					

					if (count == 0)
					{
						GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "x: -1 y: -1 (links oben)");
						m_Input.m_TargetX = -1;
						m_Input.m_TargetY = -1;
						m_Input.m_Hook = 1;
					}
					else if (count == 1)
					{
						GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "x: 1 y: 1 (rechts untern)");
						m_Input.m_TargetX = 1;
						m_Input.m_TargetY = 1;
						m_Input.m_Hook = 1;
					}
					else if (count == 2)
					{
						GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "x: 0 y: 0 (rechts)");
						m_Input.m_TargetX = 0;
						m_Input.m_TargetY = 0;
						m_Input.m_Hook = 1;
					}
					else if (count == 3)
					{
						GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "x: 0 y: -1 (rechts oben) ");
						m_Input.m_TargetX = 0;
						m_Input.m_TargetY = -1;
						m_Input.m_Hook = 1;
					}
					else if (count == 4)
					{
						GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "x: 1 y: 2 (rechts unten)");
						m_Input.m_TargetX = 1;
						m_Input.m_TargetY = 2;
						m_Input.m_Hook = 1;
					}
					else if (count == 5)
					{
						GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "x: 1 y: 0.5 (unknown)");
						m_Input.m_TargetX = 1;
						m_Input.m_TargetY = 0.5;
						m_Input.m_Hook = 1;
					}
					else if (count == 6)
					{
						GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "x: -1 y: 0 (unknown)");
						m_Input.m_TargetX = -1;
						m_Input.m_TargetY = 0;
						m_Input.m_Hook = 1;
					}

					count++;

					if (count > 5)
					{
						count = 0;
					}


					//if (m_Core.m_HookState != HOOK_GRABBED)


					// das ist die zeit, wann das nächste emote kommt
					// Server()->Tick() + Server()->TickSpeed() ist zum beispiel in einer sekunde (weil TickSpeed() eine sekunde ist)
					// Server()->Tick() + Server()->TickSpeed()*10 halt in 10 sekunden
					// rand() % 21 gibt dir eine zahl zwischen 0 und 20 aus
					// also Server()->TickSpeed() * 10 = in 10 sekunden
					// + Server()->TickSpeed() * (rand() % 21) = plus eine zufällige sekundenzahl zwischen 0 und 20
					// also irgendwas zwischen 10 und 30 sekunden
					m_EmoteTickNextFast = Server()->Tick() + Server()->TickSpeed() / 2; // NOrmal=6  // + Server()->TickSpeed() * (rand() % 21); //schnelela
				}
			}
			else
			{
				m_Input.m_Hook = 0;
				m_Input.m_Direction = -1;
			}
		}
		else if (m_pPlayer->m_DummyMode == 17)  //testy wb bot (old and shit af) xD
		{
			//rest dummy (zuruecksetzten)
			//m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;



			if (Server()->Tick() >= m_EmoteTickNext)
			{
				if (m_Core.m_Vel.x > 0)
				{
					m_Input.m_Direction = -1;
					m_Input.m_TargetX = -1;
					m_Input.m_TargetY = 0;
				}
				else if (m_Core.m_Vel.x < 0)
				{
					m_Input.m_Direction = 1;
					m_Input.m_TargetX = 0;
					m_Input.m_TargetY = 0;
				}
				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() / 15;
			}
			else
			{
				GameServer()->SendEmoticon(m_pPlayer->GetCID(),7);
			}

			//char* ChatTest;
			//sprintf(ChatTest, "%f", m_Core.m_Vel.x);

			//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, ChatTest);

			if (m_Core.m_Vel.x == 0)
			{
				m_Input.m_Direction = 0;
				m_Input.m_Hook = 0;
			}
			else if (m_Core.m_Vel.x > 0)
			{
				m_Input.m_Hook = 1;
			}
			else if (m_Core.m_Vel.x < 0)
			{
				m_Input.m_Hook = 1;
			}

		}                                //this mode <3 18 reks em all
		else if (m_pPlayer->m_DummyMode == 18)//pathlaufing system (become ze ruler xD) // ich bin der mode um den es hier geht
		{
			m_Input.m_Hook = 0;
			//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "HALLO ICH BIN 18!");

			//Check ob dem bot langweilig geworden is :)

			//m_Dummy_bored_counter = 5;

			if (m_Dummy_bored_counter > 2)
			{
				m_Dummy_bored = true;
			}


			/*
			BRAND NEW STRUCTURE!
			WELCOME TO 18's SPECIAL MODE-CEPTION!
			
			dummymode 18 hase his own modes in the mode lol


			:::::::::::::::::::::
			dummymode18 modes
			:::::::::::::::::::::
			mode:         desc:
			0					Main mode
			1					attack mode (if ruler spot is ruled and bot is in tunnel)
			2                   different wayblock mode
			3                   (PLANNED) 1on1 mode with counting in chat and helping




			dummymode18 code structure:
			- Check for activating other modes
			- big if clause with all modes

			*/


			//Check for activating other modes

			//Check mode 1 [Attack from tunnel wayblocker]
			//man könnte das auch mit m_Dummy_happy abfragen aber mich nich ganz so viel sinn
			if (m_Core.m_Pos.y > 214 * 32 && m_Core.m_Pos.x > 424 * 32)
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRulerWB(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{

					//Wenn der bot im tunnel ist und ein Gegner im RulerWB bereich
					m_Dummy_mode18 = 1;
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Wayblocker gesichtet");

				}
			}
			else if (m_Dummy_happy && m_Dummy_bored)
			{
				m_Dummy_mode18 = 2;
			}
			else if (m_Dummy_special_defend) //Check mode 3 [Attack from tunnel wayblocker]
			{
				m_Dummy_mode18 = 3;
			}
			else
			{
				m_Dummy_mode18 = 0; //change to main mode
			}

			


			//Modes:

			if (m_Dummy_mode18 == 3) //special defend mode
			{
				//testy wenn der dummy in den special defend mode gesetzt wird pusht das sein adrenalin und ihm is nicht mehr lw
				m_Dummy_bored_counter = 0;

				CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{

					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;



					m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

					//rest on tick
					m_Input.m_Hook = 0;
					m_Input.m_Jump = 0;
					m_Input.m_Direction = 0;
					m_LatestInput.m_Fire = 0;
					m_Input.m_Fire = 0;
					SetWeapon(1); //gun verwenden damit auch erkannt wird wann der mode getriggert wird


					if (pChr->m_FreezeTime == 0)
					{
						//wenn der gegner doch irgendwie unfreeze wird übergib an den main mode und lass den notstand das regeln
						m_Dummy_special_defend = false;
						m_Dummy_special_defend_attack = false;
					}
					//mode18 sub mode 3
					//Main code:
					//warte bis der gegner auf den boden geklatscht ist
					//dann werf ihn rechts runter

					if (pChr->m_Core.m_Vel.y > -0.9f && pChr->m_Pos.y > 211 * 32)
					{
						//wenn der gegner am boden liegt starte angriff
						m_Dummy_special_defend_attack = true;

						//start jump
						m_Input.m_Jump = 1;
					}


					if (m_Dummy_special_defend_attack)
					{
						if (m_Core.m_Pos.x - pChr->m_Pos.x < 50) //wenn der gegner nah genung is mach dj
						{
							m_Input.m_Jump = 1;
						}
						
						if (pChr->m_Pos.x < m_Core.m_Pos.x)
						{
							m_Input.m_Hook = 1;
						}
						else //wenn der gegner weiter rechts als der bot is lass los und übergib an main deine arbeit ist hier getahen
						{    //main mode wird evenetuell noch korrigieren mit schieben
							m_Dummy_special_defend = false;
							m_Dummy_special_defend_attack = false;
						}

						//Der bot sollte möglichst weit nach rechts gehen aber natürlich nicht ins freeze

						if (m_Core.m_Pos.x < 427 * 32 + 15)
						{
							m_Input.m_Direction = 1;
						}
						else
						{
							m_Input.m_Direction = -1;
						}

					}

				}
				else //wenn kein gegner mehr im Ruler bereich is
				{
					m_Dummy_special_defend = false;
					m_Dummy_special_defend_attack = false;
				}
			}
			else if (m_Dummy_mode18 == 2) //different wayblock mode
			{
				//rest on tick
				m_Input.m_Hook = 0;
				m_Input.m_Jump = 0;
				m_Input.m_Direction = 0;
				m_LatestInput.m_Fire = 0;
				m_Input.m_Fire = 0;
				SetWeapon(0);


				//Selfkills (bit random but they work)
				if (isFreezed)
				{
					//wenn der bot freeze is warte erstmal n paar sekunden und dann kill dich
					if (Server()->Tick() % 300 == 0)
					{
						Die(m_pPlayer->GetCID(), WEAPON_SELF);
						m_Dummy_happy = false;
					}
				}



				CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler2(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					//Check ob an notstand mode18 = 0 übergeben
					if (pChr->m_FreezeTime == 0)
					{
						m_Dummy_bored = false;
						m_Dummy_bored_counter = 0;
						m_Dummy_mode18 = 0;
					}




					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

					m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

					m_Input.m_Jump = 1;

					if (pChr->m_Pos.y > m_Core.m_Pos.y) //solange der bot über dem gegner ist (damit er wenn er ihn weg hammert nicht weiter hookt)
					{ 
						m_Input.m_Hook = 1;
					}

					if (m_Core.m_Pos.x > 420 * 32)
					{
						m_Input.m_Direction = -1;
					}

					if (pChr->m_Pos.y < m_Core.m_Pos.y + 15)
					{
						m_LatestInput.m_Fire++;
						m_Input.m_Fire++;
					}

				}
				else //lieblings position finden wenn nichts abgeht
				{
					if (m_Core.m_Pos.x < 421 * 32)
					{
						m_Input.m_Direction = 1;
					}
					else if (m_Core.m_Pos.x > 422 * 32 + 30)
					{
						m_Input.m_Direction = -1;
					}
				}
			}
			else if (m_Dummy_mode18 == 1) //attack in tunnel
			{
				//Selfkills (bit random but they work)
				if (isFreezed)
				{
					//wenn der bot freeze is warte erstmal n paar sekunden und dann kill dich
					if (Server()->Tick() % 300 == 0)
					{
						Die(m_pPlayer->GetCID(), WEAPON_SELF);
					}
				}

				//stay on position

				if (m_Core.m_Pos.x < 426 * 32 + 10) // zu weit links
				{
					m_Input.m_Direction = 1; //geh rechts
				}
				else if (m_Core.m_Pos.x > 428 * 32 - 10) //zu weit rechts
				{
					m_Input.m_Direction = -1; // geh links
				}
				else if (m_Core.m_Pos.x > 428 * 32 + 10) // viel zu weit rechts
				{
					m_Input.m_Direction = -1; // geh links
					m_Input.m_Jump = 1;
				}
				else
				{
					CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRulerWB(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{
						if (pChr->m_Pos.x < 436 * 32) //wenn er ganz weit über dem freeze auf der kante ist (hooke direkt)
						{
							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
						}
						else //wenn der Gegner weiter hinter dem unhook ist (hook über den Gegner um ihn trozdem zu treffen und das unhook zu umgehen)
						{
							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x - 50;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x - 50;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
						}


						char aBuf[256];
						str_format(aBuf, sizeof(aBuf), "targX: %d = %d - %d", m_Input.m_TargetX, pChr->m_Pos.x, m_Pos.x);
						//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);


						//m_Input.m_Hook = 0;
						CCharacter *pChr = GameServer()->m_World.ClosestCharTypeTunnel(m_Pos, true);
						if (pChr && pChr->IsAlive())
						{
							//wenn jemand im tunnel is check ob du nicht ausversehen den hookst anstatt des ziels in der WB area
							if (pChr->m_Pos.x < m_Core.m_Pos.x) //hooke nur wenn kein Gegner rechts von dem bot im tunnel is (da er sonst ziemlich wahrscheinlich den hooken würde)
							{
								m_Input.m_Hook = 1;
							}
							
						}
						else
						{
							//wenn eh keiner im tunnel is hau raus dat ding
							m_Input.m_Hook = 1;
						}

						//schau ob sich der gegner bewegt und der bot grad nicht mehr am angreifen iss dann resette falls er davor halt misshookt hat
						//geht nich -.-
					/*	if (!m_Core.m_HookState == HOOK_FLYING && !m_Core.m_HookState == HOOK_GRABBED)
						{
							if (Server()->Tick() % 10 == 0)
							m_Input.m_Hook = 0;
						}*/

		


						if (m_Core.m_Vel.x > 3.0f)
						{
							m_Input.m_Direction = -1;
						}
						else
						{
							m_Input.m_Direction = 0;
						}

					}
					else
					{
						m_Dummy_mode18 = 0;
					}
				}



			}
			else if (m_Dummy_mode18 == 0) //main mode
			{
				//if (mode18_main_init)
				//{
				//	//initialzing main mode...
				//	//resetting stuff...
				//	m_Input.m_Hook = 0;
				//}

				//m_Input.m_Hook = 0;
				//if (m_Core.m_HookState == HOOK_FLYING)
				//	m_Input.m_Hook = 1;
				//else if (m_Core.m_HookState == HOOK_GRABBED)
				//	m_Input.m_Hook = 1;
				//else
				//	m_Input.m_Hook = 0;

				m_Input.m_Jump = 0;
				m_Input.m_Direction = 0;
				m_LatestInput.m_Fire = 0;
				m_Input.m_Fire = 0;





				//char aBuf[256];
				//str_format(aBuf, sizeof(aBuf), "speed:  x: %f y: %f speed pChr:  x: %f y: %f", m_Core.m_Vel.x, m_Core.m_Vel.y);

				//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);


				if (1 == 1)
				{
					CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{
						char aBuf[256];
						str_format(aBuf, sizeof(aBuf), "speed pChr:  x: %f y: %f", pChr->m_Core.m_Vel.x, pChr->m_Core.m_Vel.y);

						//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);
					}
				}



				//m_pPlayer->m_TeeInfos.m_Name = aBuf; 

				if (m_Core.m_Vel.x > 1.0f)
				{
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "speed: schneller als 1");
				}


				//Check ob jemand in der linken freeze wand is

				CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRulerLeftFreeze(m_Pos, true);  //wenn jemand rechts im freeze liegt
				if (pChr && pChr->IsAlive()) // wenn ein spieler rechts im freeze lebt
				{  //----> versuche im notstand nicht den gegner auch da rein zu hauen da ist ja jetzt voll

					m_Dummy_left_freeze_full = true;
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Da liegt einer im freeze");
				}
				else // wenn da keiner is fülle diesen spot (linke freeze wand im ruler spot)
				{
					m_Dummy_left_freeze_full = false;
				}





				//Selfkill

				if (m_Core.m_Pos.x < 390 * 32)  //Links am spawn runter
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Links am spawn runter");
				}
				else if (m_Core.m_Pos.y < 204 * 32 && m_Core.m_Pos.x < 415 * 32) //freeze decke am spawn
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze decke am spawn");
				}
				else if (m_Core.m_Pos.y > 218 * 32 + 31 /* für tee balance*/ && m_Core.m_Pos.x < 415 * 32) //freeze boden am spawn
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze boden am spawn");
				}
				else if (m_Core.m_Pos.y < 215 * 32 && m_Core.m_Pos.y > 213 * 32 && m_Core.m_Pos.x > 415 * 32 && m_Core.m_Pos.x < 428 * 32) //freeze decke im tunnel
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze decke im tunnel");
				}
				else if (m_Core.m_Pos.y > 222 * 32) //freeze becken unter area
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze becken unter area");
				}
				else if (m_Core.m_Pos.y > 213 * 32 && m_Core.m_Pos.x > 436 * 32) //freeze rechts neben freeze becken
				{
					//Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze rechts neben freeze becken");
				}
				else if (m_Core.m_Pos.x > 469 * 32) //zu weit ganz rechts in der ruler area
				{
					//Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "zu weit ganz rechts in der ruler area");
				}
				else if (m_Core.m_Pos.y > 211 * 32 + 34 && m_Core.m_Pos.x > 455 * 32) //alles freeze am boden rechts in der area
				{
					//Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze boden rechts der area");
				}


				// Movement
				//CheckFatsOnSpawn

				if (m_Core.m_Pos.x < 406 * 32)
				{
					CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{

						m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
						m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

						m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
						m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;


						if (pChr->m_Pos.x < 407 * 32 && pChr->m_Pos.y > 212 * 32 && pChr->m_Pos.y < 215 * 32 && pChr->m_Pos.x > m_Core.m_Pos.x) //wenn ein im weg stehender tee auf der spawn plattform gefunden wurde
						{
							SetWeapon(0); //hol den hammer raus!
							if (pChr->m_Pos.x - m_Core.m_Pos.x < 30) //wenn der typ nahe bei dem bot ist
							{
								if (m_FreezeTick == 0) //nicht rum schrein
								{
									m_LatestInput.m_Fire++;
									m_Input.m_Fire++;
								}


								if (Server()->Tick() % 10 == 0)
								{
									GameServer()->SendEmoticon(m_pPlayer->GetCID(), 9); //angry
								}
							}
						}
						else
						{
							SetWeapon(1); //pack den hammer weg
						}
					}
				}


				//CheckSlowDudesInTunnel

				if (m_Core.m_Pos.x > 415 * 32 && m_Core.m_Pos.y > 214 * 32) //wenn bot im tunnel ist
				{
					CCharacter *pChr = GameServer()->m_World.ClosestCharTypeTunnel(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{
						if (pChr->m_Core.m_Vel.x < 7.8f) //wenn der nächste spieler im tunnel ein slowdude is 
						{
							//HauDenBau
							SetWeapon(0); //hol den hammer raus!

							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							if (m_FreezeTick == 0) //nicht rum schrein
							{
								m_LatestInput.m_Fire++;
								m_Input.m_Fire++;
							}

							if (Server()->Tick() % 10 == 0)  //angry emotes machen
							{
								GameServer()->SendEmoticon(m_pPlayer->GetCID(), 9);
							}


						}
					}
				}


				//CheckSpeedInTunnel
				if (m_Core.m_Pos.x > 425 * 32 && m_Core.m_Pos.y > 214 * 32 && m_Core.m_Vel.x < 9.4f) //wenn nich genung speed zum wb spot springen
				{
					m_Dummy_get_speed = true;
				}


				if (m_Dummy_get_speed) //wenn schwung holen == true (tunnel)
				{
					if (m_Core.m_Pos.x > 422 * 32) //zu weit rechts
					{
						//---> hol schwung für den jump
						m_Input.m_Direction = -1;
					}
					else //wenn weit genung links
					{
						//dann kann das normale movement von dort aus genung schwung auf bauen
						m_Dummy_get_speed = false;
					}
				}
				else
				{
					if (m_Core.m_Pos.x < 415 * 32) //bis zum tunnel laufen
					{
						m_Input.m_Direction = 1;

					}
					else if (m_Core.m_Pos.x < 440 * 32 && m_Core.m_Pos.y > 213 * 32) //im tunnel laufen
					{
						m_Input.m_Direction = 1;

					}


					//externe if abfrage weil laufen während sprinegn xD

					if (m_Core.m_Pos.x > 413 * 32 && m_Core.m_Pos.x < 415 * 32) // in den tunnel springen
					{
						m_Input.m_Jump = 1;
						//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "triggerd");
						//m_Input.m_Jump = 0;
					}
					else if (m_Core.m_Pos.x > 428 * 32 - 20 && m_Core.m_Pos.y > 213 * 32) // im tunnel springen
					{
						m_Input.m_Jump = 1;
					}



					// externen springen aufhören für dj

					if (m_Core.m_Pos.x > 428 * 32 && m_Core.m_Pos.y > 213 * 32) // im tunnel springen nicht mehr springen
					{
						m_Input.m_Jump = 0;
						//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "triggerd");
					}


					//nochmal extern weil springen während springen

					if (m_Core.m_Pos.x > 430 * 32 && m_Core.m_Pos.y > 213 * 32) // im tunnel springen springen
					{
						m_Input.m_Jump = 1;
						//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "triggerd");
					}



					if (m_Core.m_Pos.x > 431 * 32 && m_Core.m_Pos.y > 213 * 32) //jump refillen für wayblock spot
					{
						m_Input.m_Jump = 0;
					}
				}

				// *****************************************************
				// Way Block spot (Main Spot) 29 29 29 29
				// *****************************************************
				// wayblockspot < 213


				//externer wayblockspot stuff

				//Checken ob der bot in seinem arial angegriffen wird obwohl kein nostand links ausgerufen wurde



				//wird nicht genutzt weil das preventive springen vom boden aus schluss endlich schlimmer ausgeht als der dj
				/*
				if (m_Core.m_Pos.y < 213 * 32 && m_Core.m_Pos.x > (427 * 32) - 20 && m_Core.m_Pos.x < (428 * 32) + 10) //wenn der bot sich an seinem ruler spot befindet
				{
				//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich mag diesen ort :)");

				if (!m_Dummy_wb_hooked && !m_Dummy_emergency && !m_Dummy_pushing && m_Core.m_Vel.x > 0.90f) //wenn der bot sich auf das freeze zubewegt obwohl er nicht selber läuft
				{
				// --> er wird wahrscheinlich gehookt oder anderweitig extern angegriffen
				// --> schutzmaßnahmen treffen

				GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "AAAh ich werde angegriffen");
				m_Input.m_Jump = 1;
				}
				m_Dummy_pushing = false;
				m_Dummy_emergency = false;
				m_Dummy_wb_hooked = false;
				}
				*/


				//Bools zurueck setzten
				m_Dummy_pushing = false;
				m_Dummy_emergency = false;
				m_Dummy_wb_hooked = false;
				m_Dummy_happy = false;  

				//normaler internen wb spot stuff

				if (m_Core.m_Pos.y < 213 * 32)
				{
					//self kill im freeze
					//New Testy selfkill kill if isFreezed and vel 0
					if (!isFreezed || m_Core.m_Vel.x < -0.5f || m_Core.m_Vel.x > 0.5f || m_Core.m_Vel.y != 0.000000f)
					{
						//mach nichts lol brauche nur das else is einfacher
					}
					else
					{
						if (Server()->Tick() % 150 == 0)
						Die(m_pPlayer->GetCID(), WEAPON_SELF);
					}

					//Old self kill kill if freeze
					//if (m_Core.m_Pos.y < 201 * 32) // decke
					//{
					//	Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//	//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "suicide reason: roof rulerspot");
					//}
					//else if (m_Core.m_Pos.x < 417 * 32 && m_Core.m_Pos.x > 414 * 32 + 17 && isFreezed) //linker streifen xD
					//{
					//	Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//	//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "suicide reason: left wall rulerspot");
					//}


					//because shitty structure (more infos at TODO(1)) check here for enemys attacking from outside of the ruler area

					//Checken Ob ein potentieller Gegner auf der edge unter dem WBbereich ist
					//Falls diesem so sei --> mach den da weg
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "debug");
					if (1 == 1)
					{
						//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "debug");
						CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRulerWBBottom(m_Pos, true);
						if (pChr && pChr->IsAlive() && !pChr->isFreezed) //wenn jemand da so im bereich lebt und unfreeze ist
						{

							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;



							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							//erkenne gefahr
							// --> treffe gegen maßnahmen

							//lauf rum rand (bereit machen zum hooken)
							if (m_Core.m_Pos.x < 428 * 32 + 6) //wenn zu weit links um in dem winkel zu hooken 
							{
								m_Input.m_Direction = 1;
							}
							else if (m_Core.m_Pos.x > 428 * 32 + 28)
							{
								m_Input.m_Direction = -1;
							}


							//hooke 
							CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
							if (pChr && pChr->IsAlive())
							{
								//Wenn der nächste spieler unter der wb area ist hook
								//damit er wenn er einen falschen spieler gehookt hat oder sonst wie den nicht hochzieht
								if (pChr->m_Pos.y > 213 * 32 && m_Core.m_Pos.x > 427 * 32 + 3)
								{
									m_Input.m_Hook = 1;
								}
							}
						}
					}




					//TODO(1): keep this structur in mind this makes not much sence
					// the bool m_Dummy_happy is just true if a enemy is in the ruler area because all code below depends on a enemy in ruler area
					// maybe rework this shit



					//                                                      
					//                                               --->   Ruler   <---    testy own class just search in ruler area

					CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler(m_Pos, true);  //position anderer spieler mit pikus aimbot abfragen
					if (pChr && pChr->IsAlive())
					{
						//                                         old: 417 * 32
						//                                                      Old: tee<bot      New: tee<pos.x                                     
						if (pChr->m_Pos.y < 213 * 32 && pChr->m_Pos.x > 417 * 32 - 5/* && pChr->m_Pos.x < m_Core.m_Pos.x*/ && pChr->m_Pos.x < 428 * 32 && m_Core.m_Pos.x < 429 * 32 && m_Core.m_Pos.x > 415 * 32 && m_Core.m_Pos.y < 213 * 32 ||  //wenn ein tee weiter links ist als der bot && der bot links vom mittelfreeze im rulerspot steht
							pChr->m_Pos.y < 213 * 32 && pChr->m_Pos.x > 417 * 32 - 5/* && pChr->m_Pos.x < m_Core.m_Pos.x*/ && pChr->m_Pos.x < 444 * 32 && m_Core.m_Pos.x < 429 * 32 && m_Core.m_Pos.x > 415 * 32 && m_Core.m_Pos.y < 213 * 32 && pChr->m_FreezeTime == 0)       //oder der tee auch rechts vom bot ist aber unfreeze
																																																																				//wenn dies ist -> notstand links ausrufen und versuchen gegner zu blocken
						{
							//m_Core.m_ActiveWeapon = WEAPON_HAMMER;
							SetWeapon(0);


							//testy sollte eig auch am anfang des modes passen
							//m_Input.m_Direction = 0;

							//if (m_Core.m_HookState == HOOK_FLYING)
							//	m_Input.m_Hook = 1;
							//else if (m_Core.m_HookState == HOOK_GRABBED)
							//	m_Input.m_Hook = 1;
							//else
							//	m_Input.m_Hook = 0;

							char aBuf[256];
							str_format(aBuf, sizeof(aBuf), "hookstate: %x", m_Input.m_Hook);
							//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);

							m_Dummy_emergency = true;




							if (!m_Dummy_left_freeze_full)
							{
								//                                                                                                        x > 5 = 3       <-- ignorieren xD


								//                                                                                                          hier wird das schieben an das andere schieben 
								//                                                                                                    übergeben weil er hier von weiter weg anfängt zu schieben 
								//                                                                                                und das kürzere schieben macht dann den ganzen stuff das der bot nicht selber rein läuft  
								//                                                                                                ja ich weiss das ist ziemlich umständlich xD
								//                                                                                                      aber das hat schon sinn das hier wird aufgerufen wenn der weit weg is und freezed und
								//                                                                                                  übergibt dann an die abfrage die auch aufgerufen wird wenn jemand unfreeze is jedoch nir auf kurze distanz

								//                                                                                                          tja aber das mit dem übergeben klappt ja nich wirklich


								//                                                                                                           Deswegen hab ich den code ganz gelöscht und nur ein teil als || in die "freeze protection & schieberrei" geklatscht
								//                                                                                                         ----> hier is ein berg an kommentaren zu nicht existentem code lol    gut das nur ich hier rum stöber hueueueu
								//start sequenz
								// Blocke spieler in die linke freeze wand

								if (!m_Dummy_jumped)
								{
									//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "boing!");
									m_Input.m_Jump = 1;
									m_Dummy_jumped = true;
								}
								else
								{
									m_Input.m_Jump = 0;
								}



								if (!m_Dummy_hooked)
								{
									if (Server()->Tick() % 30 == 0)
										m_Dummy_hook_delay = true;

									//testy removed hook here i dont know why but all works pretty good still xD
									if (m_Dummy_hook_delay)
										//m_Input.m_Hook = 1;

									if (Server()->Tick() % 200 == 0)
									{
										m_Dummy_hooked = true;
										m_Input.m_Hook = 0;
									}

								}

								if (!m_Dummy_moved_left)
								{
									if (m_Core.m_Pos.x > 419 * 32 + 20)
										m_Input.m_Direction = -1;
									else
										m_Input.m_Direction = 1;

									if (Server()->Tick() % 200 == 0)
									{
										m_Dummy_moved_left = true;
										m_Input.m_Direction = 0;
									}

								}
							}







							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "NOTSTAND");

							if (Server()->Tick() % 30 == 0)  //angry emotes machen
							{
								GameServer()->SendEmoticon(m_pPlayer->GetCID(), 9);
							}



							CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler(m_Pos, true); //aimbot + hammerspam
							if (pChr && pChr->IsAlive())
							{

								m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
								m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
								m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
								m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;


								//schiess delay
								if (Server()->Tick() >= m_EmoteTickNext)
								{
									m_pPlayer->m_LastEmote = Server()->Tick();


									//GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);

									if (m_FreezeTick == 0) //nicht rum schrein
									{
										m_LatestInput.m_Fire++;
										m_Input.m_Fire++;
									}

									m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() / 4;
								}
							}







							//Blocke gefreezte gegner für immer 


							//TODO:
							//das is ein linke seite block wenn hier voll is sollte man anders vorgehen
							//                           früher war es y > 210   aber change weil er während er ihn hochzieht dann nicht mehr das hooken aufhört
							if (pChr->m_FreezeTime > 0 && pChr->m_Pos.y > 204 * 32 && pChr->m_Pos.x > 422 * 32) //wenn ein gegner weit genung rechts freeze am boden liegt
							{
								// soll der bot sich einer position links des spielers nähern
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "hab n opfer gefunden");

								if (m_Core.m_Pos.x + (5 * 32 + 40) < pChr->m_Pos.x) // er versucht 5 tiles links des gefreezten gegner zu kommen
								{
									m_Input.m_Direction = -1;

									if (m_Core.m_Pos.x > pChr->m_Pos.x && m_Core.m_Pos.x < pChr->m_Pos.x + (4 * 32)) // wenn er 4 tiles rechts des gefreezten gegners is
									{
										m_Input.m_Jump = 1;
										//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "boing!");
									}
								}
								else //wenn der bot links des gefreezten spielers is
								{
									m_Input.m_Jump = 1;
									//echo jump
									//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "boing!");

									m_Input.m_Direction = -1;

									if (m_Core.m_Pos.x < pChr->m_Pos.x) //solange der bot weiter links is
									{
										m_Input.m_Hook = 1;
									}
									else
									{
										m_Input.m_Hook = 0;
									}
								}
							}






							//freeze protection & schieberrei
							//                                                                                                                                                                                                      old (417 * 32 - 60)
							if (pChr->m_Pos.x + 10 < m_Core.m_Pos.x && pChr->m_Pos.y > 211 * 32 && pChr->m_Pos.x < 418 * 32 || pChr->m_FreezeTime > 0 && pChr->m_Pos.y > 210 * 32 && pChr->m_Pos.x < m_Core.m_Pos.x && pChr->m_Pos.x > 417 * 32 - 60) // wenn der spieler neben der linken wand linken freeze wand liegt schiebt ihn der bot rein
							{                                                                                            // oder wenn der spieler weiter weg liegt aber freeze is


								if (!m_Dummy_left_freeze_full) //wenn da niemand is schieb den rein
								{
									// HIER TESTY TESTY CHANGES  211 * 32 + 40 stand hier
									if (pChr->m_Pos.y > 211 * 32 + 40) // wenn der gegner wirklich ganz tief genung is
									{ //                          417 * 32 - 40
										if (m_Core.m_Pos.x > 418 * 32) // aber nicht selber ins freeze laufen
										{
											m_Input.m_Direction = -1;




											//Check ob der gegener freeze is

											if (pChr->m_FreezeTime > 0)
											{
												m_LatestInput.m_Fire = 0; //nicht schiessen ofc xD (doch is schon besser xD)
												m_Input.m_Fire = 0;

												//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "haha owned");
											}

											//letzten stupser geben (sonst gibs bugs kb zu fixen)
											if (pChr->isFreezed) //wenn er schon im freeze is
											{
												m_LatestInput.m_Fire = 1; //hau ihn an die wand
												m_Input.m_Fire = 1;
											}

										}
										else
										{
											m_Input.m_Direction = 1;
											//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "stop error code: 1");
											if (pChr->m_FreezeTime > 0)
											{
												m_LatestInput.m_Fire = 0; //nicht schiessen ofc xD (doch is schon besser xD)
												m_Input.m_Fire = 0;

												//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "haha owned");
											}
											//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "ich halte das auf.");
											//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich will da nich rein laufen");
										}



									}
									else //wenn der gegner nicht tief genung ist
									{

										m_Input.m_Direction = 1;

										if (pChr->m_FreezeTime > 0)
										{
											m_LatestInput.m_Fire = 0; //nicht schiessen ofc xD (doch is schon besser xD)
											m_Input.m_Fire = 0;

											//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "haha owned");
										}
									}



								}
								else //wenn da schon jemand liegt 
								{
									// sag das mal xD
									//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "da liegt schon einer");
								}
							}
							else if (m_Core.m_Pos.x < 419 * 32 + 10) //sonst mehr abstand halten
							{
								m_Input.m_Direction = 1;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "stop error code: 2");
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich will da nich rein laufen");
							}
							// else // wenn nichts los is erstmal stehen bleiben 






							//freeze protection decke mit double jump wenn hammer

							if (m_Core.m_Vel.y < 20.0f && m_Core.m_Pos.y < 207 * 32)  // wenn der tee nach oben gehammert wird
							{
								if (m_Core.m_Pos.y > 206 * 32) //ab 206 würd er so oder so ins freeze springen
									m_Input.m_Jump = 1;

								if (m_Core.m_Pos.y < pChr->m_Pos.y) //wenn der bot über dem spieler is soll er hooken
									m_Input.m_Hook = 1;
								else
									m_Input.m_Hook = 0;
							}


							//wenn der tee hcoh geschleudert wird
							//                 old 4 (macht aber im postiven bereich kein sinn aber hat geklappt)
							//                 HALLO HIER IST DEIN ICH AUS DER ZUKUNFT: du dummes kind wenn er in der luft hammert dann fliegt er doch nicht nach oben und gerade da musst du es ja perfekt haben ... low
							//if (m_Core.m_Vel.y < 4.0f && m_Core.m_Pos.y < pChr->m_Pos.y) //wenn er schneller als 4 nach oben fliegt und höher als der Gegener ist
							// lass das mit speed weg und mach lieber was mit höhe
							if (m_Core.m_Pos.y < 207 * 32 && m_Core.m_Pos.y < pChr->m_Pos.y)
							{
								//in hammer position bewegen
								if (m_Core.m_Pos.x > 418 * 32 + 20) //nicht ins freeze laufen
								{
									if (m_Core.m_Pos.x > pChr->m_Pos.x - 45) //zu weit rechts von hammer position
									{
										m_Input.m_Direction = -1; //gehe links
																  //GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich will da nich rein laufen");
									}
									else if (m_Core.m_Pos.x < pChr->m_Pos.x - 39) // zu weit links von hammer position
									{
										m_Input.m_Direction = 1;
										//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "stop error code: 3");
									}
									else  //im hammer bereich
									{
										m_Input.m_Direction = 0; //bleib da
									}
								}
							}


							//Check ob der gegener freeze is

							if (pChr->m_FreezeTime > 0 && pChr->m_Pos.y > 208 * 32 && !pChr->isFreezed) //wenn der Gegner tief und freeze is macht es wenig sinn den frei zu hammern
							{
								m_LatestInput.m_Fire = 0; //nicht schiessen 
								m_Input.m_Fire = 0;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "haha owned");
							}



							//Hau den weg (wie dummymode 21)
							if (pChr->m_Pos.x > 418 * 32 && pChr->m_Pos.y > 209 * 32)  //das ganze findet nur im bereich statt wo sonst eh nichts passiert
							{
								//wenn der bot den gegner nicht boosten würde hammer den auch nich weg
								m_LatestInput.m_Fire = 0;
								m_Input.m_Fire = 0;

								if (pChr->m_Core.m_Vel.y < -0.5f && m_Core.m_Pos.y + 15 > pChr->m_Pos.y) //wenn der dude speed nach oben hat
								{
									m_Input.m_Jump = 1;
									if (m_FreezeTime == 0)
									{
										m_LatestInput.m_Fire++;
										m_Input.m_Fire++;
									}
								}
							}


							//TODO: FIX:
							//der bot unfreezed den gegner ab einer gewissen höhe wenn er rein gehammert wird schau das da was passiert





							//wenn ein tee freeze links neben dem bot liegt werf den einfach wieder ins freeze becken
							//das is bisher ja noch die einzige sicherheits lücke beim wayblocken
							//wenn man ein tee über den bot hammert

							if (pChr->m_Pos.x > 421 * 32 && pChr->m_FreezeTick > 0 && pChr->m_Pos.x < m_Core.m_Pos.x)
							{
								m_Input.m_Jump = 1;
								m_Input.m_Hook = 1;
							}


							//m_pPlayer->m_TeeInfos.m_ColorBody = (0 * 255 / 360);
							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Enemy in ruler spot found!");
						}
						else //sonst normal wayblocken und 427 aufsuchen
						{
							//m_Core.m_ActiveWeapon = WEAPON_GUN;
							SetWeapon(1);
							m_Input.m_Jump = 0;

							if (m_Core.m_HookState == HOOK_FLYING)
								m_Input.m_Hook = 1;
							else if (m_Core.m_HookState == HOOK_GRABBED)
								m_Input.m_Hook = 1;
							else
								m_Input.m_Hook = 0;

							//m_pPlayer->m_TeeInfos.m_ColorBody = (120 * 255 / 360);
							//positions check and correction 427


							m_Dummy_jumped = false;
							m_Dummy_hooked = false;
							m_Dummy_moved_left = false;



							if (m_Core.m_Pos.x > 428 * 32 + 15 && m_Dummy_ruled) //wenn viel zu weit ausserhalb der ruler area wo der bot nur hingehookt werden kann
							{
								m_Input.m_Jump = 1;
								m_Input.m_Hook = 1;
							}

							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Prüfe ob zu weit rechts");
							if (m_Core.m_Pos.x < (427 * 32) - 20) // zu weit links -> geh rechts
							{
								m_Input.m_Direction = 1;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "stop error code: 4");
							}
							else if (m_Core.m_Pos.x >(428 * 32) + 10) // zu weit rechts -> geh links
							{
								m_Input.m_Direction = -1;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich bin zuweit rechts...");
							}
							else // im toleranz bereich -> stehen bleiben
							{
								m_Dummy_happy = true;
								m_Dummy_ruled = true;
								m_Input.m_Direction = 0;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "toleranz bereich");
								//m_Input.m_LatestTargetX = 0;
								//m_Input.m_LatestTargetY = 0;


								//stuff im toleranz bereich doon


					


								// normal wayblock
								CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);  //position anderer spieler mit pikus aimbot abfragen
								if (pChr && pChr->IsAlive())
								{
									//Check ob jemand special angeflogen kommt dann mode18 = 3 starten
									//Check ob special_defend aktiviert werden sollte
									if (pChr->m_Pos.x < 431 * 32 && pChr->m_Core.m_Vel.y < -12.5f && pChr->m_Core.m_Vel.x < -7.4f)
									{
										m_Dummy_special_defend = true;
									}

									//debuggn special_defend
									char aBuf[256];
									str_format(aBuf, sizeof(aBuf), "speed pChr:  x: %f y: %f", pChr->m_Core.m_Vel.x, pChr->m_Core.m_Vel.y);
									GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);

									//m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
									//m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;



									//m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
									//m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

									//m_Input.m_TargetX = 1;//pChr->m_Pos.x - m_Pos.x; //1
									//m_Input.m_TargetY = 0;//pChr->m_Pos.y - m_Pos.y; //0

									//m_LatestInput.m_TargetX = 1;//pChr->m_Pos.x - m_Pos.x;
									//m_LatestInput.m_TargetY = 0;//pChr->m_Pos.y - m_Pos.y;

									if (pChr->m_Pos.y < 213 * 32 + 10 && pChr->m_Pos.x < 430 * 32 && pChr->m_Pos.y > 210 * 32 && pChr->m_Pos.x > 416 * 32 + 32) // wenn ein spieler auf der linken seite in der ruler area is 
									{
										//wenn der typ über dem freze irgendwo rum fliegt

										if (pChr->m_Pos.y < 212 * 32 - 10)  //wenn er jedoch zu hoch zum schieben ist
										{
											//mach dich bereit zu schieben und geh nach links (aufziehen)
											m_Input.m_Direction = -1;
										}
										else  //wenn er tief genung zum schieben ist
										{
											if (m_Core.m_Pos.x < 428 * 32 + 10) //bei (429 * 32) gibts voll jiggle xD
											{
												m_Input.m_Direction = 1; //schieb ihn runter
												m_Dummy_pushing = true;
											}
											else
											{
												m_Input.m_Direction = 0; // aber nicht zu weit
																		 //GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "ja ich bin das!");
											}
										}
									}
									else // wenn spieler irgendwo anders is
									{




										//CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler(m_Pos, true);  //wenn jemand oben is
										//if (pChr && pChr->IsAlive())
										//{
										//		m_Input.m_Hook = 1;
										//		m_Dummy_wb_hooked = true;
										//		GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);

										//}





										if (!m_Dummy_emergency) //wayblock stuff hook ja nein pipapo nicht im notfall
										{
											CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRulerWB(m_Pos, true);  //wenn jemand oben is (nur im wb bereich)
											if (pChr && pChr->IsAlive())
											{                                                                  // und er nicht zu tief ist (das is um unnötiges festgehalte zu verhindern) (bringt eh nichts weil das hier dann nicht mehr aufgerufen wird weil der dann nicht mehr in ClosesestCharTypeRulerWB ist -.-)
												m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
												m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;



												m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
												m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
												//GameServer()->SendEmoticon(m_pPlayer->GetCID(), 8);
												//                             noch eine vel abfrage weil der bot sonst daneben hookt
												if (pChr->m_Pos.y > 211 * 32 && pChr->m_Core.m_Vel.y > -1.0f && pChr->m_Core.m_Vel.y < 2.0f && pChr->m_Pos.x > 435 * 32/*&& pChr->m_Pos.y < 213 * 32*/) //wenn er nich zu schnell nach oben fliegt und zu weit oben ist
												{



													//m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x; //1
													//m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y; //0


													
												


													m_Input.m_Hook = 0;
													m_Input.m_Hook = 1;
													m_Dummy_wb_hooked = true;
													if (Server()->Tick() % 30 == 0) //nicht zu hart spammen wenn iwas abgeht
													{
														GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);
														m_Dummy_bored_counter++; //zähl mal mit wie lange der bot hier rum gurkt und wieviele spieler er so wayblockt
														char aBuf[256];
														str_format(aBuf, sizeof(aBuf), "dummy_bored_count: %d", m_Dummy_bored_counter);
														GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);
													}
												}
											}
											else
											{
												if (Server()->Tick() % 10 == 0) //nicht zu hart spammen wenn iwas abgeht
													GameServer()->SendEmoticon(m_pPlayer->GetCID(), 15);
												m_Input.m_Hook = 0;
												//GameServer()->SendEmoticon(m_pPlayer->GetCID(), 3);
											}
										}
										//unnötiges festgehalte unten verhindern
										if (!m_Dummy_emergency) //auch hier wieder nur wenn kein notfall is
										{
											CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
											if (pChr && pChr->IsAlive())
											{
												if (pChr->m_Pos.y > 213 * 32 - 5 && m_Core.m_HookState == HOOK_GRABBED && pChr->m_Pos.y < 213 * 32 + 5)
												{
													//Wenn folgendes:
													// kein notstand
													// der bot wenn am haken hat
													// der nächste spieler aber unter der ruler area ist (genauer gesagt gerade im freeze eingetaucht)
													// --> vermute ich mal das er genau diesen spieler hookt
													// --> den los lassen da dieser sowieso keien gefahr mehr ist damit ein neuer gegner schneller geblockt werden kann
													if (Server()->Tick() % 10 == 0) //nicht zu hart spammen wenn iwas abgeht
														GameServer()->SendEmoticon(m_pPlayer->GetCID(), 5);


													m_Input.m_Hook = 0;
												}
											}
										}


								
										//if (Server()->Tick() % 50 == 0) //hook ihn xD
										//{
										//	//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "bin im bereich");
										//	if (m_Input.m_Hook == 0)
										//	{
										//		m_Input.m_Hook = 1;
										//		m_Dummy_wb_hooked = true;
										//		//GameServer()->SendEmoticon(m_pPlayer->GetCID(), 1);
										//		//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "huke");
										//		//schiess delay
										//		if (Server()->Tick() >= m_EmoteTickNext)
										//		{
										//			m_pPlayer->m_LastEmote = Server()->Tick();


										//			//GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);

										//			m_LatestInput.m_Fire++;
										//			m_Input.m_Fire++;

										//			m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() / 4;
										//		}
										//		else
										//		{
										//			m_LatestInput.m_Fire = 0;
										//			m_Input.m_Fire = 0;
										//		}
										//	}
										//	else
										//	{
										//		m_Input.m_Hook = 0;
										//		GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);
										//		//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "huke nich");

										//	}
										//}

									}
								}
							}
						}
					}
					else // wenn kein lebender spieler im ruler spot ist
					{

						//Suche trozdem 427 auf

						if (m_Core.m_Pos.x < (427 * 32) - 20) // zu weit links -> geh rechts
						{
							m_Input.m_Direction = 1;
							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "stop error code: special");
						}
						else if (m_Core.m_Pos.x >(427 * 32) + 40) // zu weit rechts -> geh links
						{
							m_Input.m_Direction = -1;
							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich bin zuweit rechts...");
						}
					}






					// über das freeze springen wenn rechts der bevorzugenten camp stelle

					if (m_Core.m_Pos.x > 434 * 32)
					{
						m_Input.m_Jump = 1;
					}
					else if (m_Core.m_Pos.x > (434 * 32) - 20 && m_Core.m_Pos.x < (434 * 32) + 20) // bei flug über freeze jump wd holen
					{
						m_Input.m_Jump = 0;
						//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "refilling jump");
					}







				}


				//testy vel

				/*

				if (m_Core.m_Vel.x == 16 * 32)
				{
				GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "speed: 16");
				}

				*/


				//ganz am ende nochmal checken ob man nicht gerade einen spieler wieder aus dem freeze zieht
				//TODO: wenn hier irgendwann eine protection kommt das der spieler nicht ganz an der linken wand sein sollte
				// muss das hier geändert wwwerden


				if (1 < 10)
				{
					CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRulerLeftFreeze(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{
						if (pChr->isFreezed && pChr->m_Pos.x < 417 * 32 - 30) //wenn ein gegner in der linken wand is
						{
							m_Input.m_Hook = 0; //hook den da mal wd nich raus
						}
					}
				}

				//das selbe auch rechts

				if (1 < 10)
				{
					CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{    // heieiie aber natürlich auch hoch genung is das der bot noch wayblocken kann
						if (pChr->m_FreezeTime > 0 && pChr->m_Pos.x > 428 * 32 + 40 && pChr->m_Pos.y < 211 * 32) //wenn ein gegner in der linken wand is
						{
							m_Input.m_Hook = 0; //hook den da mal wd nich raus
						}
					}
				}


				//TESTY to prevent bugs
				//wenn kein notfall is und der bot glücklich mit seiner position ist
				//dann sollte er auch nicht springen und somit irgendwie spielern helfen die er gerade hookt

				if (!m_Dummy_emergency && m_Dummy_happy)
				{
					m_Input.m_Jump = 0;
				}


			
			}
			else //Change to mode main and reset all
			{
				GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "EROOR!!!!");
				//RestOnChange (zuruecksetzten)
				m_Input.m_Hook = 0;
				m_Input.m_Jump = 0;
				m_Input.m_Direction = 0;
				m_LatestInput.m_Fire = 0;
				m_Input.m_Fire = 0;



				m_Dummy_mode18 = 0;
			}

		}
		else if (m_pPlayer->m_DummyMode == 19) //   new testy dynamic random stuff dooer on chillblock5                          old: dummydummy hammerfly (driver)
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;
			

			CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
			if (pChr && pChr->IsAlive())
			{

				m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
				m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

				//balance auf sein kopf xD
				if (pChr->m_Pos.y > m_Core.m_Pos.y)
				{
					if (pChr->m_Pos.x + 1 < m_Core.m_Pos.x) //wenn zu weit rechts
					{
						m_Input.m_Direction = -1;
						m_DummyDriveDuration = 0;
					}
					else if (m_Core.m_Pos.x + 1 < pChr->m_Pos.x) //wenn zu weit links
					{
						m_Input.m_Direction = 1;
						m_DummyDriveDuration = 0;
					}
					else
					{
						if (pChr->m_Pos.y - m_Core.m_Pos.y < 9 * 32) //hook wenn nah genung dran
						{
							m_Input.m_Hook = 1;
						}	
						//speedfly dj
						if (pChr->IsGrounded() == false)
						{
							m_DummyDriveDuration++;
						}
						if (m_DummyDriveDuration > 600)
						{
							if (pChr->m_Pos.y - m_Core.m_Pos.y < 41 && pChr->IsGrounded() == false)
							{
								m_Input.m_Jump = 1;
							}
							m_DummyDriveDuration = 0;
						}
						//resett hook new when too near
						if (pChr->m_Pos.y - m_Core.m_Pos.y < 45)
						{
							m_Input.m_Hook = 0;
						}
						//resett hook old
						//if (Server()->Tick() % 40 == 0)
						//{
						//	m_Input.m_Hook = 0;
						//}
					}
				}



			}

		}
		else if (m_pPlayer->m_DummyMode == 20) // dummydummy hammerfly (hammer)
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;
			SetWeapon(0);

			CCharacter *pChr = GameServer()->m_World.ClosestCharTypeDummy(m_Pos, true);
			if (pChr && pChr->IsAlive())
			{

				m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

				m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;


				//wenn der driver druff is
				if (pChr->m_Pos.y < m_Core.m_Pos.y)
				{
					if (Server()->Tick() % 25 == 0) //hammer tick
					{
						m_LatestInput.m_Fire++;
						m_Input.m_Fire++;
					}
				}
			}
		}
		else if (m_pPlayer->m_DummyMode == 21) // up hammer troll
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;
			SetWeapon(0);

			CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
			if (pChr && pChr->IsAlive())
			{
				m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

				m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;


				//lauf zu dem hin
				//nur wenn der nächste spieler grad nach ooben fliegt oder auf der selben höhe ist
				if (pChr->m_Pos.y == m_Core.m_Pos.y || pChr->m_Core.m_Vel.y < -0.4f)
				{
					if (pChr->m_Pos.y >= m_Core.m_Pos.y)
					{
						if (pChr->m_Pos.x + 1 < m_Core.m_Pos.x) //wenn zu weit rechts
						{
							m_Input.m_Direction = -1;
						}
						else if (m_Core.m_Pos.x + 1 < pChr->m_Pos.x) //wenn zu weit links
						{
							m_Input.m_Direction = 1;
						}
					}
				}

				//und wenn der hoch springt
				//hau den weg xD
				if (pChr->m_Core.m_Vel.y < -0.5f && m_Core.m_Pos.y + 15 > pChr->m_Pos.y) //wenn der dude speed nach oben hat
				{
					m_Input.m_Jump = 1;
					if (m_FreezeTime == 0)
					{
						m_LatestInput.m_Fire++;
						m_Input.m_Fire++;
					}
				}

			}

		}
		else if (m_pPlayer->m_DummyMode == 22)  //friend test mode
		{
			CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
			if (pChr && pChr->IsAlive())
			{
				//Debuggin
				char aBuf[256];
				str_format(aBuf, sizeof(aBuf), "FriendID: %d pChr: %d ", m_Dummy_FriendID, pChr->GetPlayer()->GetCID());
				GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);


				//huiuiu wie verwende ich dasn jetzt hier?
				//ah du bist wd weg?
				//ja gut dann noch net ,s osomuss muss aber jetz gleich kurz afk wie kann ich hier chekcen ob pChr-> ein freund is?
				// musst du wissen. ich hab kein plan von deiner struktur
				// hmkay

				//struktur ^^

				/*
				    ne der dummy is nix xD und der andere spieler is pChr yy
					m_pPlayer is der dummy und pChr der spieler? dann steht doch im dummy der name vom freund drin
					das vergleichst du einfach mit dem namen von pChr
					bin dann kurz weg, bis gleich
				*/

				//Server()->PlayerName(clientid)

				/*
					die funktion liefert dir entweder -1, 0 oder 1 zurück
					0 bei gleichheit
					-1 wenn der zweite string im alphabet vornedran is (oder hintendran)
					1 halt umgekehrt
					also bei str_comp("A", "B") kommt entweder -1 oder 1 raus, weiß grad nicht mehr genau (weil B weiter hintendran is im alphabet)

					wenn du die abfrage ohne ! machst, fragt es ab, ob die zahl ungleich 0 ist. mit dem ! halt ob es gleich null ist
					, also im prinzip ob die beiden strings übereinstimmen tschüssxD
					toll erklärt :)
					sollte nu gehen
				*/
				//if (!str_comp(m_Dummy_friend, Server()->ClientName(pChr->GetPlayer()->GetCID()))) //so? oder halt so das isn int
				if(m_Dummy_FriendID == pChr->GetPlayer()->GetCID())
				{
					if (Server()->Tick() % 30 == 0)
					GameServer()->SendEmoticon(m_pPlayer->GetCID(), 2);
				}
			}
		}
		else if (m_pPlayer->m_DummyMode == 23) //Race mode ChillBlock5 with humans
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;
			m_Dummy_mode23 = 0;

			/*
			Dummy23modes:
			0				Classic Main race mode.
			1				Tricky mode with tricky hammerfly and sensless harder hammerhit xD. (used for "Drag*" to fuck him in the race lol)
			2				ChillerDragon's mode just speedhammerfly.
			
			*/

			if (1 == 1)
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					//if (Server()->ClientName(pChr) == "ChillerDragon")
					if (
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "Starkiller") ||
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "rqza") ||
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "timakro") ||
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "destin T'nP") ||
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "Destin") ||
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "Ante") ||
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "Ama") ||
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "Forris") ||
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "Aoe") ||
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "Spyker") ||
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "Waschlappen") ||
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), ".:Mivv") || 
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "nealson T'nP") || 
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "ChillerDragon") || 
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "ChillerDragon.*") || 
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "BeckyHill") || 
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "Blue") || 
						!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "pro")
						)
					{
						m_Dummy_mode23 = 2;
					}
					if (!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "Drag*"))
					{
						m_Dummy_mode23 = 1;
					}
				}
			}



			//Selfkill
			
			//Checken ob der bot far im race ist
			if (m_Dummy_collected_weapons && m_Core.m_Pos.x > 470 * 32 && m_Core.m_Pos.y < 200 * 32)
			{
				//TODO:
				//schau wie weit der bot is wenn er weiter is als der ClosestCharTypeFarInRace bereich is schau das du rechtzeitig n anderen triggerst
				//wie zumbeispiel ClosestCharTypeFinish und das wird getriggert wenn der bot rechts des 2p parts is oder so

				CCharacter *pChr = GameServer()->m_World.ClosestCharTypeFarInRace(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
				}
				else
				{
					if (!isFreezed || m_Core.m_Vel.x < -0.5f || m_Core.m_Vel.x > 0.5f || m_Core.m_Vel.y != 0.000000f)
					{
						//mach nichts lol brauche nur das else is einfacher
					}
					else
					{
						if (Server()->Tick() % 370 == 0)
							Die(m_pPlayer->GetCID(), WEAPON_SELF);
					}
				}
			}
			else //sonst normal relativ schnell killen
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					if (!isFreezed || m_Core.m_Vel.x < -0.5f || m_Core.m_Vel.x > 0.5f || m_Core.m_Vel.y != 0.000000f)
					{
						//mach nichts lol brauche nur das else is einfacher
					}
					else
					{
						if (Server()->Tick() % 270 == 0)
							Die(m_pPlayer->GetCID(), WEAPON_SELF);
					}
				}
				else
				{
					if (isFreezed && m_Core.m_Vel.y == 0.000000f && m_Core.m_Vel.x < 0.1f && m_Core.m_Vel.x > -0.1f)
					{
						Die(m_pPlayer->GetCID(), WEAPON_SELF);
					}
				}
			}
			





			//insta self kills
			if (m_Core.m_Pos.x < 390 * 32)  //Links am spawn runter
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
				//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Links am spawn runter");
			}
			else if (m_Core.m_Pos.y < 204 * 32 && m_Core.m_Pos.x < 415 * 32) //freeze decke am spawn
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
				//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze decke am spawn");
			}
			else if (m_Core.m_Pos.y > 218 * 32 + 31 /* für tee balance*/ && m_Core.m_Pos.x < 415 * 32) //freeze boden am spawn
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
				//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze boden am spawn");
			}
			else if (m_Core.m_Pos.y < 215 * 32 && m_Core.m_Pos.y > 213 * 32 && m_Core.m_Pos.x > 415 * 32 && m_Core.m_Pos.x < 428 * 32) //freeze decke im tunnel
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
				//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze decke im tunnel");
			}
			else if (m_Core.m_Pos.y > 222 * 32) //freeze becken unter area
			{
				//Die(m_pPlayer->GetCID(), WEAPON_SELF);
				//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze becken unter area");
			}


			//Movement bis zur ruler area:
			/*
			NEW! Movement modes for the basic move till hammerfly!
			m_Dummy_movement_mode23 is a int to check which movement style the bot shoudl used

			0					normal old basic mode
			1					new mode jump left side up into ruler area [ALPHA]


			i dunno how to set the modes for now its hardcodet set to 1 maybe add a random switcher or depending on how frustrated the bot is
			
			*/
			m_Dummy_movement_mode23 = 0;




			if (m_Dummy_movement_mode23 == 0)
			{
				if (m_Core.m_Pos.x < 415 * 32) //bis zum tunnel laufen
				{
					m_Input.m_Direction = 1;

				}
				else if (m_Core.m_Pos.x < 440 * 32 && m_Core.m_Pos.y > 213 * 32) //im tunnel laufen
				{
					m_Input.m_Direction = 1;
					if (m_Core.m_Vel.x < 5.5f)
					{
						m_Input.m_TargetY = -3;
						m_Input.m_TargetX = 200;
						m_LatestInput.m_TargetY = -3;
						m_LatestInput.m_TargetX = 200;

						if (Server()->Tick() % 30 == 0)
						{
							SetWeapon(0);
						}
						if (Server()->Tick() % 55 == 0)
						{
							if (m_FreezeTime == 0)
							{
								m_Input.m_Fire++;
								m_LatestInput.m_Fire++;
							}
						}
						if (Server()->Tick() % 200 == 0)
						{
							m_Input.m_Jump = 1;
						}
					}
				}


				//externe if abfrage weil laufen während sprinegn xD

				if (m_Core.m_Pos.x > 413 * 32 && m_Core.m_Pos.x < 415 * 32) // in den tunnel springen
				{
					m_Input.m_Jump = 1;
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "triggerd");
					//m_Input.m_Jump = 0;
				}
				else if (m_Core.m_Pos.x > 428 * 32 - 20 && m_Core.m_Pos.y > 213 * 32) // im tunnel springen
				{
					m_Input.m_Jump = 1;
				}



				// externen springen aufhören für dj

				if (m_Core.m_Pos.x > 428 * 32 && m_Core.m_Pos.y > 213 * 32) // im tunnel springen nicht mehr springen
				{
					m_Input.m_Jump = 0;
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "triggerd");
				}


				//nochmal extern weil springen während springen

				if (m_Core.m_Pos.x > 430 * 32 && m_Core.m_Pos.y > 213 * 32) // im tunnel springen springen
				{
					m_Input.m_Jump = 1;
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "triggerd");
				}



				if (m_Core.m_Pos.x > 431 * 32 && m_Core.m_Pos.y > 213 * 32) //jump refillen für wayblock spot
				{
					m_Input.m_Jump = 0;
				}
			}
			else if (m_Dummy_movement_mode23 == 1) //enter ruler area with a left jump 
			{
				if (m_Core.m_Pos.x < 415 * 32) //bis zum tunnel laufen
				{
					m_Input.m_Direction = 1;

				}
				else if (m_Core.m_Pos.x < 440 * 32 && m_Core.m_Pos.y > 213 * 32) //im tunnel laufen
				{
					if (m_Core.m_Pos.x > 426 * 32)
					{
						//if (m_Core.m_Vel.x < 11.4f) //slow down before jump
						//{
							m_Input.m_Direction = 1;
						//}
					}
					else
					{
						m_Input.m_Direction = 1;
					}
				}

				//springen
				if (m_Core.m_Pos.x > 413 * 32 && m_Core.m_Pos.x < 415 * 32 && m_Core.m_Pos.y > 213 * 32) // in den tunnel springen
				{
					m_Input.m_Jump = 1;
				}
				else if (m_Core.m_Pos.x > 428 * 32 - 3 && m_Core.m_Pos.y > 217 * 32 && m_Core.m_Pos.y > 213 * 32) // im tunnel springen
				{
					m_Input.m_Jump = 1;
				}


				//nochmal extern weil springen während springen


				if (m_Core.m_Pos.x > 429 * 32 - 18)
				{
					m_Input.m_Direction = -1;
				}

				if (m_Core.m_Pos.y < 217 * 32 && m_Core.m_Pos.x > 420 * 32 && m_Core.m_Pos.y > 213 * 32 + 20)
				{
					//m_Input.m_Direction = -1;
					if (m_Core.m_Pos.y < 216 * 32) // im tunnel springen springen
					{
						m_Input.m_Jump = 1;
					}
				}

				//originaly made for a yt video but is ok to keep it there
				//if (m_Core.m_Pos.y > 2)


			}

			//MoVement ab dem ruler spot weiter laufen
			//NEW! wenn er links vom freeze becken im ruler spot is also beim wb spot des 18er modes dann jump übers freeze
			if (m_Core.m_Pos.y < 213 * 32 && m_Core.m_Pos.x > 428 * 32 && m_Core.m_Pos.x < 429 * 32)
			{
				m_Input.m_Jump = 1;
			}


			if (m_Core.m_Pos.x > 417 * 32 && m_Core.m_Pos.y < 213 * 32 && m_Core.m_Pos.x < 450 * 32) //vom ruler nach rechts nachm unfreeze werden
			{
				m_Input.m_Direction = 1;
			}

			if (m_Core.m_Pos.x > 439 * 32 && m_Core.m_Pos.y < 213 * 32 && m_Core.m_Pos.x < 441 * 32) //über das freeze zum hf start springen
			{
				m_Input.m_Jump = 1;
			}

			if (m_Core.m_Pos.y > 200 * 32 && m_Core.m_Pos.x > 457 * 32)
			{
				m_Input.m_Direction = -1;
			}

			//unnötiger dj
			//if (m_Core.m_Pos.x > 441 * 32 + 10 && m_Core.m_Pos.y < 213 * 32 && m_Core.m_Pos.x < 442 * 32)
			//{
			//	m_Input.m_Jump = 1;
			//}



			//Jetzt kommt der schwierige rocketjump part o.O mal sehen wie gut das hinhaut xD
			//TODO:
			//aufpassen dass er das ganze nur macht wenn er nicht schon beim 2p part ist
			if (m_Dummy_collected_weapons)
			{
				if (m_Core.m_Pos.x < 466 * 32)
				{
					SetWeapon(3);
				}
				//prepare for rocktjump


				if (m_Core.m_Pos.x < 451 * 32 + 1 && m_Core.m_Pos.y > 209 * 32) //wenn zu weit links für rj
				{
					m_Input.m_Direction = 1;
				}
				else if (m_Core.m_Pos.x > 451 * 32 + 3 && m_Core.m_Pos.y > 209 * 32) //wenn zu weit links für rj
				{
					m_Input.m_Direction = -1;
				}
				else
				{
					if (m_Core.m_Vel.x < 0.01f && m_Core.m_Vel.x > -0.01f) //nahezu stillstand
					{
						//ROCKETJUMP
						if (m_Core.m_Pos.x > 450 * 32 && m_Core.m_Pos.y > 209 * 32)
						{
							//Wenn der bot weit genung is und ne waffe hat und tief genung is 
							// ---> bereit machen für rocketjump
							//damit der bot nicht ausm popo schiesst xD

							m_Input.m_TargetX = 0;
							m_Input.m_TargetY = 37;
							m_LatestInput.m_TargetX = 0;
							m_LatestInput.m_TargetY = 37;
						}

						if (m_Core.m_Pos.y > 210 * 32 + 30 && !isFreezed) //wenn der dummy auf dem boden steht und unfreeze is
						{
							if (m_Core.m_Vel.y == 0.000000f)
							{
								m_Input.m_Jump = 1;
							}
						}

						if (m_Core.m_Pos.y > 210 * 32 + 10 && m_Core.m_Vel.y < -0.9f && !isFreezed) //dann schiessen
						{
							//m_LatestInput.m_TargetX = 0;
							//m_LatestInput.m_TargetY = 10;
							m_LatestInput.m_Fire++;
							m_Input.m_Fire++;
						}

				
					}
				}
			}



			if (m_Core.m_Pos.x > 448 * 32 && m_Core.m_Pos.x < 458 * 32 && m_Core.m_Pos.y > 209 * 32) //wenn der bot auf der platform is
			{
				//nicht zu schnell laufen
				if (Server()->Tick() % 3 == 0)
				{
					m_Input.m_Direction = 0;
					//GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);
				}
			}

			//Rocketjump2 an der freeze wand
			//prepare aim!
			if (m_Core.m_Pos.y < 196 * 32)
			{
				m_Input.m_TargetX = -55;
				m_Input.m_TargetY = 32;
				m_LatestInput.m_TargetX = -55;
				m_LatestInput.m_TargetY = 32;
			}

			if (m_Core.m_Pos.x < 452 * 32 && m_Core.m_Pos.y > 188 * 32 && m_Core.m_Pos.y < 192 * 32 && m_Core.m_Vel.y < 0.1f && m_Dummy_collected_weapons)
			{
				m_Dummy_rjumped2 = true;
				m_LatestInput.m_Fire++;
				m_Input.m_Fire++;
			}
				
			//Fliegen nach rj2
			if (m_Dummy_rjumped2)
			{
				m_Input.m_Direction = 1;


				if (m_Core.m_Pos.x > 461 * 32 && m_Core.m_Pos.y > 192 * 32 + 20)
				{
					m_Input.m_Jump = 1;
				}

				if (m_Core.m_Pos.x > 478 * 32 || m_Core.m_Pos.y > 196 * 32)
				{
					m_Dummy_rjumped2 = false;
				}
			}


			//Check ob der dummy schon waffen hat
			if (m_Core.m_Pos.y < 165 * 32 && m_Core.m_Pos.x > 451 * 32 - 10 && m_Core.m_Pos.x < 454 * 32 + 10)
			{
				m_Dummy_collected_weapons = true;
			}

			if (1 == 0.5 + 0.5)
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					if (pChr->m_Pos.y < 165 * 32 && pChr->m_Pos.x > 451 * 32 - 10 && pChr->m_Pos.x < 454 * 32 + 10)
					{
						m_Dummy_mate_collected_weapons = true;
					}
				}
			}

			//Hammerfly
			if (m_Core.m_Pos.x > 447 * 32)
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					//unfreezemates on platform

					//Get closer to the mate
					if (pChr->m_Pos.y == m_Core.m_Pos.y && m_Core.m_Pos.x > 450 * 32 && m_Core.m_Pos.x < 457 * 32 && pChr->m_FreezeTime > 0)
					{
						if (pChr->m_Pos.x > m_Core.m_Pos.x + 70) //if friend is on the right of the bot
						{
							m_Input.m_Direction = 1;

						}
						else if (pChr->m_Pos.x < m_Core.m_Pos.x - 70) //if firend is on the left of the bot
						{
							m_Input.m_Direction = -1;

						}
					}

					//Hammer mate if near enough
					if (m_Core.m_Pos.x < 456 * 32 + 20 && pChr->m_FreezeTime > 0 && m_Core.m_Pos.y > 209 * 32 && pChr->m_Pos.y > 209 * 32 && pChr->m_Pos.x > 449 * 32 && pChr->m_Pos.x < 457 * 32)
					{
						if (pChr->m_Pos.x > m_Core.m_Pos.x - 60 && pChr->m_Pos.x < m_Core.m_Pos.x + 60)
						{
							if (m_Core.m_ActiveWeapon == WEAPON_HAMMER && m_FreezeTime == 0)
							{
								m_Input.m_Fire++;
								m_LatestInput.m_Fire++;
								m_Dummy_hook_mate_after_hammer = true;
							}
						}
					}
					if (m_Dummy_hook_mate_after_hammer)
					{
						if (pChr->m_Core.m_Vel.x < -0.3f || pChr->m_Core.m_Vel.x > 0.3f)
						{
							m_Input.m_Hook = 1;
						}
						else
						{
							m_Dummy_hook_mate_after_hammer = false;
						}

						//stop this hook after some time to prevent nonstop hooking if something went wrong
						if (Server()->Tick() % 100 == 0)
						{
							m_Dummy_hook_mate_after_hammer = false;
						}

					}

					if (pChr->isFreezed)
					{
						m_Dummy_help_before_fly = true;
					}
					if (pChr->m_FreezeTime == 0)
					{
						m_Dummy_help_before_fly = false;
					}
				}

				if (m_Dummy_help_before_fly)
				{
					if (!m_Dummy_collected_weapons)
					{
						if (Server()->Tick() % 20 == 0)
						{
							SetWeapon(0);
						}
						CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
						if (pChr && pChr->IsAlive())
						{
							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							//GameServer()->SendEmoticon(m_pPlayer->GetCID(), 2);

							//Check where help is needed
							if (pChr->m_Pos.x > 457 * 32 + 10 && pChr->m_Pos.x < 468 * 32 && pChr->m_Pos.y < 213 * 32 + 5) //right freeze becken
							{
								//Get in help position:
								if (m_Core.m_Pos.x < 457 * 32 - 1)
								{
									m_Input.m_Direction = 1;
								}
								else if (m_Core.m_Pos.x > 457 * 32 + 8)
								{
									m_Input.m_Direction = -1;
								}

								//jump 
								if (m_Core.m_Vel.y == 0.000000f && m_FreezeTime == 0 && m_Core.m_Pos.y > 209 * 32)
								{
									if (Server()->Tick() % 16 == 0)
									{
										m_Input.m_Jump = 1;
									}
								}

								//hook
								if (m_Core.m_Pos.y < pChr->m_Pos.y - 60 && pChr->m_FreezeTime > 0)
								{
									m_Input.m_Hook = 1;
									if (m_Core.m_Pos.x > 454 * 32)
									{
										m_Input.m_Direction = -1;
									}
								}

								//unfreezehammer
								if (pChr->m_Pos.x < m_Core.m_Pos.x + 60 && pChr->m_Pos.x > m_Core.m_Pos.x - 60 && pChr->m_Pos.y < m_Core.m_Pos.y + 60 && pChr->m_Pos.y > m_Core.m_Pos.y - 60)
								{
									if (m_FreezeTime == 0)
									{
										m_Input.m_Fire++;
										m_LatestInput.m_Fire++;
									}
								}

							}
							else if (pChr->m_Pos.x > 469 * 32 + 20 && pChr->m_Pos.x < 480 * 32 && pChr->m_Pos.y < 213 * 32 + 5 && pChr->m_Pos.y > 202 * 32)
							{
								//Get in help position:
								if (m_Core.m_Pos.x < 467 * 32)
								{
									if (m_Core.m_Pos.x < 458 * 32)
									{
										if (m_Core.m_Vel.y == 0.000000f)
										{
											m_Input.m_Direction = 1;
										}
									}
									else
									{
										m_Input.m_Direction = 1;
									}

									if (m_Core.m_Vel.y > 0.2f || m_Core.m_Pos.y > 212 * 32)
									{
										m_Input.m_Jump = 1;
									}
								}
								if (m_Core.m_Pos.x > 469 * 32)
								{
									m_Input.m_Direction = -1;
									if (m_Core.m_Vel.y > 0.2f || m_Core.m_Pos.y > 212 * 32)
									{
										m_Input.m_Jump = 1;
									}
								}

								//jump 
								if (m_Core.m_Vel.y == 0.000000f && m_FreezeTime == 0 && m_Core.m_Pos.y > 209 * 32 && m_Core.m_Pos.x > 466 * 32)
								{
									if (Server()->Tick() % 16 == 0)
									{
										m_Input.m_Jump = 1;
									}
								}

								//hook
								if (m_Core.m_Pos.y < pChr->m_Pos.y - 60 && pChr->m_FreezeTime > 0)
								{
									m_Input.m_Hook = 1;
									if (m_Core.m_Pos.x > 468 * 32)
									{
										m_Input.m_Direction = -1;
									}
								}

								//unfreezehammer
								if (pChr->m_Pos.x < m_Core.m_Pos.x + 60 && pChr->m_Pos.x > m_Core.m_Pos.x - 60 && pChr->m_Pos.y < m_Core.m_Pos.y + 60 && pChr->m_Pos.y > m_Core.m_Pos.y - 60)
								{
									if (m_FreezeTime == 0)
									{
										m_Input.m_Fire++;
										m_LatestInput.m_Fire++;
									}
								}

							}
							else //unknown area
							{
								m_Dummy_help_before_fly = false;
							}
						}
					}
				}
				//else  //old else new is if because the bot can stop helping if the closestplayer is in a unknown area fail
				if (!m_Dummy_help_before_fly)
				{
					//                                 fuck off mate i go solo fggt xD
					if (!m_Dummy_collected_weapons /*|| !m_Dummy_mate_collected_weapons*/)
					{
						if (Server()->Tick() % 20 == 0)
						{
							SetWeapon(0);
						}

						CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
						if (pChr && pChr->IsAlive())
						{
							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							//Hammerfly normal way
							if (m_Dummy_mode23 == 0)
							{
								//shot schiessen schissen
								//im freeze nicht schiessen
								if (m_DummyFreezed == false)
								{
									m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
									m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

									//schiess delay
									if (Server()->Tick() >= m_EmoteTickNext && pChr->m_Pos.y < 212 * 32 - 5)
									{
										m_pPlayer->m_LastEmote = Server()->Tick();


										GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);

										m_LatestInput.m_Fire++;
										m_Input.m_Fire++;

										m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() / 2;
									}

									//wenn schon nah an der nade
									if (m_Core.m_Pos.y < 167 * 32)
									{
										m_Input.m_Jump = 1;

										if (m_Core.m_Pos.x < 453 * 32 - 8)
										{
											m_Input.m_Direction = 1;
										}
										else if (m_Core.m_Pos.x > 454 * 32 + 8)
										{
											m_Input.m_Direction = -1;
										}
									}

								}
								else if (m_DummyFreezed == true) //if (m_DummyFreezed == false)
								{
									m_LatestInput.m_Fire = 0;
									m_Input.m_Fire = 0;
									m_DummyFreezed = false;
									//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "hey im freezded lul xD");
								}
								else
								{
									//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "iwas is maechtig flasch gelaufen du bob");
								}
							}
							else if (m_Dummy_mode23 == 2) //Speedhammerfly for ChillerDragon
							{
								//lauf zu dem hin
								//nur wenn der nächste spieler grad nach ooben fliegt oder auf der selben höhe ist
								if (pChr->m_Pos.y == m_Core.m_Pos.y || pChr->m_Core.m_Vel.y < -0.4f)
								{
									if (pChr->m_Pos.y >= m_Core.m_Pos.y)
									{
										if (pChr->m_Pos.x + 1 < m_Core.m_Pos.x) //wenn zu weit rechts
										{
											if (m_Core.m_Pos.x > 452 * 32)
												m_Input.m_Direction = -1;
										}
										else if (m_Core.m_Pos.x + 1 < pChr->m_Pos.x) //wenn zu weit links
										{
											if (m_Core.m_Pos.x < 455 * 32)
												m_Input.m_Direction = 1;
										}
									}
								}

								//und wenn der hoch springt
								//hau den weg xD
								if (pChr->m_Core.m_Vel.y < -0.5f && m_Core.m_Pos.y + 15 > pChr->m_Pos.y) //wenn der dude speed nach oben hat
								{
									m_Input.m_Jump = 1;
									if (m_FreezeTime == 0)
									{
										m_LatestInput.m_Fire++;
										m_Input.m_Fire++;
									}
								}
							}
							else
							{
								if (Server()->Tick() % 600 == 0)
								{
									GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "for this dummymode23 is no hammerflytype set :c");
								}
							}
						}
					}
				}
			}


			//Der krasse shit!
			//Der bot macht den 2Player part o.O
			//erstmal schauen wann der bot den 2player part machen soll

			//if (m_Core.m_Pos.x > 466 * 32)
			//{
			//	CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
			//	if (pChr && pChr->IsAlive())
			//	{
			//		m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
			//		m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
			//		m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
			//		m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

			//		if (m_Dummy_collected_weapons && m_FreezeTime == 0 && m_Core.m_Pos.x > 478 * 32 && m_Core.m_Pos.x < 485 * 32 && pChr->m_Pos.x > 476 * 32)
			//		{
			//			SetWeapon(0);


			//			if (pChr->m_Pos.x < m_Core.m_Pos.x && m_Core.m_Pos.x > 481 * 32 && pChr->m_Pos.y < 195 * 32) //wenn sich der racemate zum schieben eignet schieb ihn zum abgrund um ihn dort dann später zu hammern
			//			{
			//				m_Input.m_Direction = -1;
			//			}

			//			if (pChr->m_Pos.x < m_Core.m_Pos.x && m_Core.m_Pos.x - pChr->m_Pos.x < 8 && m_Core.m_Pos.x > 481 * 32 - 1) //wenn der racemate links des bots bereit um ins freeze gehammert zu werden liegt hau raus
			//			{
			//				m_Input.m_Fire++;
			//				m_LatestInput.m_Fire++;
			//			}

			//			if (pChr->m_Pos.y > 194 * 32 && m_Core.m_Pos.x < 481 * 32 && pChr->m_Pos.x < m_Core.m_Pos.x && pChr->m_Core.m_Vel.y > -0.5f) //wenn der racemate unter der platform ist und der bot geeigent zum draggen is ---> gogo
			//			{
			//				m_Dummy_dd_hook = true;
			//			}

			//			//TODO: 
			//			//abfrage die m_Dummy_dd_hook wieder auf false setzt (wenn pChr zu tief is oder zu weit rechts oder der hammer gehittet hat)

			//			if (m_Dummy_dd_hook)
			//			{
			//				m_Input.m_Hook = 1;
			//				m_Input.m_Direction = 1;

			//				if (pChr->m_Pos.x > 485 * 32)
			//				{
			//					m_Input.m_Jump = true;
			//				}
			//			}
			//		}
			//	}
			//}

			/*
			New Stuff:
			commented out the whole old system

			Struct:

			STRUCT[1]: Check if bot shoudl change m_Dummy_2p_state 

			STRUCT[2]: Let the bot do stuff depenging on m_Dummy_2p_state

			States:
			-2				Help pChr out of freeze
			-1				do nothing
			0				prepare for making the part (gettin in the right position)
			1				starting to do the part -> walking left and hammerin'
			2				keep going doing the part -> hookin' and walking to the right
			3				final stage of doing the part -> jumpin' and unfreeze pChr with hammerhit
			4				jump in freeze and let the mate help

			5				go on edge if pChr dragged u through the part --> then sg and unfreeze

			*/

			if (m_Core.m_Pos.y < 200 * 32)
			{
				//check ob der mate fail ist
				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					//                                                                                      NEW: to recognize mates freeze in the freeze tunnel on the left
					if (pChr->m_Pos.y > 198 * 32 + 10 && pChr->isFreezed && pChr->m_Core.m_Vel.y == 0.000000f || pChr->m_Pos.y < 198 * 32 + 10 && pChr->m_Pos.x < 472 * 32 && pChr->isFreezed && pChr->m_Core.m_Vel.y == 0.000000f)
					{
						m_Dummy_mate_failed = true;
					}
					if (pChr->m_FreezeTime == 0)
					{
						m_Dummy_mate_failed = false;
					}
				}


				//schau ob der bot den part geschafft hat und auf state -1 gehen soll
				if (m_Core.m_Pos.x > 485 * 32)
				{
					m_Dummy_2p_state = -1; //part geschafft --> mach aus 
				}


				if (m_Core.m_Pos.x > 466 * 32)
				{
					static int LockedID;
					CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{
						m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
						m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
						m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
						m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

						if (m_Dummy_collected_weapons && m_FreezeTime == 0 && m_Core.m_Pos.x > 478 * 32 && m_Core.m_Pos.x < 485 * 32 && pChr->m_Pos.x > 476 * 32)
						{
							//New direct in state
							//if (m_Dummy_2p_state == 1)
							//SetWeapon(0);


							//Reset Checkbools

							//if (!m_Core.m_HookState == HOOK_GRABBED && m_Dummy_2p_hook_grabbed) //wenn der bot denkt er grabbt ihn noch aber schon los gelassen hat --> fang von vorne an
							//{
							//	m_Dummy_2p_hook = false;
							//}

							if (pChr->m_Pos.y > 198 * 32) //wenn pChr iwiw runter gefallen is dann mach den hook weg
							{
								m_Dummy_2p_hook = false;
							}


							//STRUCT[1]: Check if bot shoudl change m_Dummy_2p_state
							if (m_Core.m_Pos.x < 477 * 32 || m_Dummy_mate_failed) //TODO: add if pChr wants to make the part
							{
								m_Dummy_2p_state = -1;
							}
							//                                                                                     || neu resette wenn der spieler kurz von der platform springt
							// NEW: added the bool to not start doing the part while helping
							if (m_Core.m_Pos.x > 477 * 32 && m_Core.m_Pos.x < 485 * 32 && m_Core.m_Pos.y < 195 * 32  /*|| pChr->m_Pos.x < 476 * 32 - 11 || pChr->m_Pos.y < 191 * 32*/) //alle states die mit anfangen zutuen haben nur wenn der bot auch in position steht den part zu machen
							{
								if (pChr->m_FreezeTime == 0 && m_FreezeTime == 0) //wenn beide unfreeze sind zeih auf
								{
									m_Dummy_2p_state = 0;
									//m_Dummy_2p_hook = false;
									//m_Dummy_2p_hook_grabbed = false;
								}
								//																								// NEW testy || stuff
								if (m_Core.m_Pos.x > pChr->m_Pos.x && pChr->m_Pos.y == m_Core.m_Pos.y && m_Core.m_Pos.x > 481 * 32 || pChr->m_Pos.x > 476 * 32 - 10 && m_Core.m_Pos.x > pChr->m_Pos.x && pChr->m_Pos.y > 191 * 32 - 10 && m_Core.m_Pos.x < 482 * 32 + 10)
								{
									m_Dummy_2p_state = 1; //starting to do the part->walking left and hammerin'
									if (Server()->Tick() % 30 == 0 && m_Dummy_nothing_happens_counter == 0)
									{
										SetWeapon(0);
									}
									//m_Dummy_2p_hammer1 = false;
								}
								//                                                                                 NEW TESTY || stuff     wenn der schonmal ausgelöst wurde bleib da bis der nexte ausgelöst wird oder pChr runter fällt
								if (m_Dummy_2p_state == 1 && pChr->m_Core.m_Vel.y > 0.5f && pChr->m_Pos.x < 479 * 32 || m_Dummy_2p_hook)
								{
									m_Dummy_2p_state = 2; //keep going doing the part->hookin' and walking to the right
									m_Dummy_2p_hook = true;
									/*						if (m_Core.m_HookState == HOOK_GRABBED)
									{
									m_Dummy_2p_hook_grabbed = true;
									}*/
								}

								if (m_Dummy_2p_state == 2 && pChr->m_Pos.x > 485 * 32 + 8)
								{
									m_Dummy_2p_state = 3; //final stage of doing the part->jumpin' and unfreeze pChr with hammerhit
								}

								//           NICHT NACH FREEZE ABRAGEN damit der bot auch ins freeze springt wenn das team fail ist und dann selfkill macht
								if (pChr->m_Pos.x > 489 * 32 || pChr->m_Pos.x > 486 * 32 && pChr->m_Pos.y < 186 * 32) //Wenn grad gehammert und der tee weit genugn is spring rein
								{
									m_Dummy_2p_state = 4;
								}

								//state=? 5
								if (m_FreezeTime == 0 && m_Core.m_Pos.x > 485 * 32 && pChr->m_Pos.x < 485 * 32) //wenn der bot rechts und unfreeze is und der mate noch links
								{
									m_Dummy_2p_state = 5;
								}

							
								if (pChr->m_Pos.y < 191 * 32 && pChr->m_Pos.x < 486 * 32) //resette auf state=0 wenn pChr springt
								{
									//TODO:
									//das auch mal aus machen auch wenn nichts abbricht
									m_Dummy_2p_hook = false;
								}

								//testy set the bot to mode -1 if mate fails 
								if (m_Dummy_mate_failed)
								{
									m_Dummy_2p_state = -1;
								}

							}



							//STRUCT[2]: Let the bot do stuff depenging on m_Dummy_2p_state


							if (m_Dummy_2p_state == 0) //prepare doing the part (gettin right pos)
							{
								m_Input.m_Direction = 1; //walking right until state 1 gets triggerd 
														 //GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "debug [1]");
							}
							else if (m_Dummy_2p_state == 1) //starting to do the part -> walking left and hammerin'
							{
								if (m_Core.m_Pos.x > 480 * 32 - 15) //lauf nach links bis zur hammer pos
								{
									m_Input.m_Direction = -1;
								}

								if (pChr->m_Pos.x < 480 * 32) //wenn pChr weit gwenung zum hammern is
								{
									m_Input.m_Fire++;
									m_LatestInput.m_Fire++;
									//m_Dummy_2p_hammer1 = true;
								}

								//testy stop mate if hammer was too hard and mate fly to far
								if (pChr->m_Pos.x < 478 * 32)
								{
									m_Input.m_Hook = 1;
								}

							}
							else if (m_Dummy_2p_state == 2) //keep going doing the part->hookin' and walking to the right
							{
								if (pChr->m_Pos.y > 194 * 32 + 10)
									m_Input.m_Hook = 1;

								if (pChr->m_Pos.y < 197 * 32)
									m_Input.m_Direction = 1;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "debug [2]");
							}
							else if (m_Dummy_2p_state == 3) //final stage of doing the part->jumpin' and unfreeze pChr with hammerhit
							{
								if (Server()->Tick() % 30 == 0)
								{
									SetWeapon(0); //hammer
								}

								if (pChr->m_FreezeTime > 0) //keep holding hook untill pChr is unfreeze
								{
									m_Input.m_Hook = 1;
								}

								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "debug [3]");
								m_Input.m_Direction = 1;
								m_Input.m_Jump = 1;

								//Now tricky part the unfreeze hammer
								if (pChr->m_Pos.y - m_Core.m_Pos.y < 7 && m_FreezeTime == 0) //wenn der abstand der beiden tees nach oben weniger is als 7 ^^
								{
									m_Input.m_Fire++;
									m_LatestInput.m_Fire++;
								}
							}
							//MOVED TO EXTERN CUZ SPECIAL
							//else if (m_Dummy_2p_state == 4) //PART geschafft! spring ins freeze
							//{
							//	if (m_Core.m_Pos.y < 195 * 32 && m_Core.m_Pos.x > 478 * 32) //wenn der bot noch auf der plattform is
							//	{
							//		m_Input.m_Direction = -1; //geh links bisse fällst
							//	}
							//	else //wenn de fällst
							//	{
							//		m_Input.m_Direction = 1;
							//	}
							//}
						}

						//Mega externen stuff is der state4 weil der ausm gültigeitsbereich (platform) raus läuft und so der is halt was beonders deswegen steht der an einer besonder verwirrenden stelle -.-
						if (!m_Dummy_mate_failed && m_Dummy_2p_state == 4) //PART geschafft! spring ins freeze
						{
							//Shotgun boost xD
							SetWeapon(2);
							m_Input.m_TargetX = 1;
							m_Input.m_TargetY = 1;
							m_LatestInput.m_TargetX = 1;
							m_LatestInput.m_TargetY = 1;



							if (m_Core.m_Pos.y < 195 * 32 && m_Core.m_Pos.x > 478 * 32 - 15) //wenn der bot noch auf der plattform is
							{
								if (m_Core.m_Pos.x < 480 * 32)  //wenn er schon knapp an der kante is
								{
									//nicht zu schnell laufen
									if (Server()->Tick() % 5 == 0)
									{
										m_Input.m_Direction = -1; //geh links bisse fällst
									}
								}
								else
								{
									m_Input.m_Direction = -1;
								}
							}
							else //wenn de fällst
							{
								m_Input.m_Direction = 1;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "debug [4]");
							}

							//DJ ins freeze
							if (m_Core.m_Pos.y > 195 * 32 + 10)
							{
								m_Input.m_Jump = 1;
							}

							if (m_Input.m_Direction == 1 && m_FreezeTime == 0)
							{
								m_Input.m_Fire++;
								m_LatestInput.m_Fire++;
							}

						}
						else if (m_Dummy_2p_state == 5) //made the part --> help mate
						{
							if (pChr->m_FreezeTime == 0 && pChr->m_Pos.x > 485 * 32)
							{
								m_Dummy_2p_state = -1;
							}

							if (m_Core.m_Pos.x < 192 * 32 - 30) //zu weit links
							{
								m_Input.m_Direction = 1;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "debug [5]");

								if (m_Core.m_Pos.x > 490 * 32) //wenn schon knapp dran
								{
									//nur langsam laufen (bissl bremsen)
									if (Server()->Tick() % 2 == 0)
									{
										m_Input.m_Direction = 0;
									}
								}
							}
						}
						//else if (m_Dummy_2p_state == -2) //auch extern weil der dummy vlt mal von der platform springt zum helfen
						//if (m_Dummy_mate_failed && m_Dummy_2p_state < 1)    <--- added m_Dummy_mate_failed to the state checks
						if (m_Dummy_mate_failed)
						{
							//The bot coudl fall of the plattform and hurt but this var helps to activate and accident
							//sometimes the special stage causes a jump on purpose and the var gets true so no emergency can be called
							//to make this possible agian reset this var every tick here 
							//m_Dummy_help_no_emergency is used to allow the emergency help
							m_Dummy_help_no_emergency = false;



							if (Server()->Tick() % 20 == 0)
							{
								GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);
							}

							//Go on left edge to help:
							if (m_Core.m_Pos.x > 479 * 32 + 4) //to much right
							{
								if (m_Core.m_Pos.x < 480 * 32 - 25)
								{
									if (Server()->Tick() % 9 == 0)
									{
										m_Input.m_Direction = -1;
									}
								}
								else
								{
									m_Input.m_Direction = -1;
									m_Input.m_TargetX = 300;
									m_Input.m_TargetY = -10;
									m_LatestInput.m_TargetX = 300;
									m_LatestInput.m_TargetY = -10;
								}

								if (m_Core.m_Vel.x < -1.5f && m_Core.m_Pos.x < 480 * 32)
								{
									m_Input.m_Direction = 0;
								}
							}
							else if (m_Core.m_Pos.x < 479 * 32 - 1)
							{
								m_Input.m_Direction = 1;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "debug [6]");
							}

							//Get mate with shotgun in right position:
							//if (pChr->m_Pos.x < 479 * 32 + 6) //if the mate is left enough to get shotgunned from the edge
							if (pChr->m_Pos.x < 478 * 32)
							{
								if (Server()->Tick() % 30 == 0)
								{
									SetWeapon(2); //switch to sg
								}

								if (m_FreezeTime == 0 && pChr->m_Core.m_Vel.y == 0.000000f && pChr->m_Core.m_Vel.x < 0.007f && pChr->m_Core.m_Vel.x > -0.007f && m_Core.m_Pos.x < 480 * 32)
								{
									m_Input.m_Fire++;
									m_LatestInput.m_Fire++;
								}
							}
							else //if right enough to stop sg
							{
								if (pChr->m_Pos.x < 479 * 32)
								{
									if (pChr->m_Pos.y > 194 * 32)
									{
										if (pChr->m_Core.m_Pos.y > 197 * 32)
										{
											m_Input.m_Hook = 1;
										}
										//reset hook if something went wrong
										if (Server()->Tick() % 90 == 0 && pChr->m_Core.m_Vel.y == 0.000000f) //if the bot shoudl hook but the mate lays on the ground --> resett hook
										{
											m_Input.m_Hook = 0;
											m_Dummy_nothing_happens_counter++;
											if (m_Dummy_nothing_happens_counter > 2)
											{
												if (m_Core.m_Pos.x > 478 * 32 - 1 && m_Core.m_Jumped == 0)
												{
													m_Input.m_Direction = -1;
												}
												m_Input.m_TargetX = m_Input.m_TargetX - 5;
												m_LatestInput.m_TargetX = m_LatestInput.m_TargetX - 5;
											}
											if (m_Dummy_nothing_happens_counter > 4) //warning long time nothing happend! do crazy stuff
											{
												if (m_FreezeTime == 0)
												{
													m_Input.m_Fire++;
													m_LatestInput.m_Fire++;
												}
											}
											if (m_Dummy_nothing_happens_counter > 5) //high warning mate coudl get bored --> swtich through all weapons and move angel back
											{
												SetWeapon(m_Dummy_panic_weapon);
												m_Dummy_panic_weapon++;
												m_Input.m_TargetX++;
												m_LatestInput.m_TargetX++;
											}
										}
										if (pChr->m_Core.m_Vel.y != 0.000000f)
										{
											m_Dummy_nothing_happens_counter = 0;
										}
									}

								}
								else 
								{
									if (Server()->Tick() % 50 == 0)
									{
										SetWeapon(2);
									}
									if (m_Core.m_ActiveWeapon == WEAPON_SHOTGUN && m_FreezeTime == 0)
									{
										if (pChr->m_Pos.y < 198 * 32) //if mate is high enough
										{
											m_Input.m_TargetX = -200;
											m_Input.m_TargetY = 30;
											m_LatestInput.m_TargetX = -200;
											m_LatestInput.m_TargetY = 30;
											m_Input.m_Fire++;
											m_LatestInput.m_Fire++;
										}
										else //if mate is too low --> change angel or move depnding on the x position
										{
											if (pChr->m_Pos.x < 481 * 32 - 4) //left enough to get him with other shotgun angels from the edge
											{
												//first go on the leftest possible pos on the edge
												if (m_Core.m_Vel.x > -0.0004f && m_Core.m_Pos.x > 478 * 32 - 2 && m_Core.m_Jumped == 0)
												{
													m_Input.m_Direction = -1;
												}
												/*
												[PLANNED BUT NOT NEEDED]: add more help modes and switch trough them. for now just help mode 2 is used and the int to swtich modes is usless
												Then start to help.
												There are different help modes to have some variations if nothing happens
												help modes:

												1				Old way of helping try to wallshot staright down (doesnt work)
												2				New alternative! wallshot the left wall while jumping

												*/
												m_Dummy_mate_help_mode = 2;

												if (m_Dummy_mate_help_mode == 2) //new (jump and wallshot the left wall)
												{
													if (m_Core.m_Pos.y > 193 * 32 && m_Core.m_Vel.y == 0.000000f)
													{
														if (Server()->Tick() % 30 == 0)
														{
															m_Input.m_Jump = 1;
															SetWeapon(2); //switch to sg
														}
													}

													if (m_Core.m_Pos.y < 191 * 32) //prepare aim
													{

														m_Input.m_TargetX = -300;
														m_Input.m_TargetY = 200;
														m_LatestInput.m_TargetX = -300;
														m_LatestInput.m_TargetY = 200;

														if (m_Core.m_Pos.y < 192 * 32 - 30) //shoot
														{
															if (m_FreezeTime == 0 && m_Core.m_ActiveWeapon == WEAPON_SHOTGUN && m_Core.m_Vel.y < -0.5f)
															{
																m_Input.m_Fire++;
																m_LatestInput.m_Fire++;
															}
														}
													}


													//Panic if fall of platform
													if (m_Core.m_Pos.y > 195 * 32 + 5)
													{
														m_Input.m_Jump = 1;
														m_Input.m_Direction = 1;
														m_Input.m_TargetX = 300;
														m_Input.m_TargetY = -2;
														m_LatestInput.m_TargetX = 300;
														m_LatestInput.m_TargetY = -2;
														m_Dummy_2p_panic_while_helping = true;
													}
													if (m_Core.m_Pos.x > 480 * 32 && m_FreezeTime == 0 || m_FreezeTime > 0) //stop this mode if the bot made it back to the platform or failed
													{
														m_Dummy_2p_panic_while_helping = false;
													}
													if (m_Dummy_2p_panic_while_helping)
													{
														m_Input.m_Direction = 1;
														m_Input.m_TargetX = 300;
														m_Input.m_TargetY = -2;
														m_LatestInput.m_TargetX = 300;
														m_LatestInput.m_TargetY = -2;
													}

												}
												else if (m_Dummy_mate_help_mode == 1) //old (shooting straight down from edge and try to wallshot)
												{
													m_Input.m_TargetX = 15;
													m_Input.m_TargetY = 300;
													m_LatestInput.m_TargetX = 15;
													m_LatestInput.m_TargetY = 300;
													if (m_Core.m_Vel.x > -0.1f && m_FreezeTime == 0)
													{
														m_Input.m_Fire++;
														m_LatestInput.m_Fire++;
													}

													if (m_Core.m_Pos.y > 195 * 32 + 5)
													{
														m_Input.m_Jump = 1;
														m_Input.m_Direction = 0; //old 1
														m_Input.m_TargetX = 300;
														m_Input.m_TargetY = -2;
														m_LatestInput.m_TargetX = 300;
														m_LatestInput.m_TargetY = -2;
														m_Dummy_2p_panic_while_helping = true;
													}
													if (m_Core.m_Pos.x > 480 * 32 && m_FreezeTime == 0 || m_FreezeTime > 0) //stop this mode if the bot made it back to the platform or failed
													{
														m_Dummy_2p_panic_while_helping = false;
													}
													if (m_Dummy_2p_panic_while_helping)
													{
														if (m_Core.m_Pos.y < 196 * 32 - 8)
														{
															m_Input.m_Direction = 1;
														}
														else
														{
															m_Input.m_Direction = 0;
														}
														m_Input.m_TargetX = 300;
														m_Input.m_TargetY = -2;
														m_LatestInput.m_TargetX = 300;
														m_LatestInput.m_TargetY = -2;
													}
												}
											}
											else //if mate is far and dummy has to jump of the platform and shotgun him
											{
												//in this stage of helping the bot jumps of the platform on purpose
												//m_Dummy_help_no_emergency is used to prevent the an emergency because its planned
												m_Dummy_help_no_emergency = true;

												if (Server()->Tick() % 30 == 0)
												{
													SetWeapon(2);
												}
												//go down and jump
												if (m_Core.m_Jumped >= 2) //if bot has no jump
												{
													m_Input.m_Direction = 1;
												}
												else
												{
													m_Input.m_Direction = -1;

													if (m_Core.m_Pos.x < 477 * 32 && m_Core.m_Vel.x < -3.4f) //dont rush too hard intro nowehre 
													{
														m_Input.m_Direction = 0;
													}

													if (m_Core.m_Pos.y > 195 * 32) //prepare aim
													{
														m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
														m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
														m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
														m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

														if (m_Core.m_Pos.y > 196 * 32 + 25 || m_Core.m_Pos.x < 475 * 32 + 15)
														{
															m_Input.m_Fire++;
															m_LatestInput.m_Fire++;
															m_Input.m_Jump = 1;
														}

														if (pChr->m_Pos.x < 486 * 32 && m_Core.m_Pos.y > 195 * 32 + 20 || pChr->m_Pos.x < 486 * 32 && m_Core.m_Pos.x < 477 * 32) //if mate is in range add a hook
														{
															m_Dummy_dd_helphook = true;
														}
														if (m_Core.m_Pos.x > 479 * 32)
														{
															m_Dummy_dd_helphook = false;
														}

														if (m_Dummy_dd_helphook)
														{
															m_Input.m_Hook = 1;
														}
													}
												}
											}
										}
									}
								}
							}

							if (m_Core.m_Pos.y < pChr->m_Pos.y + 40 && pChr->m_Pos.x < 479 * 32 + 10 && m_FreezeTime == 0) //if the mate is near enough to hammer
							{
								//dont switch to hammer because without delay it sucks
								//and with delay its too slow
								//the bot shoudl anyways have a hammer ready in this situation
								// so ---> just shoot
								m_Input.m_Fire++;
								m_LatestInput.m_Fire++;
							}


							//do something if nothing happens cuz the bot is stuck somehow
							if (Server()->Tick() % 100 == 0 && pChr->m_Core.m_Vel.y == 0.000000f && m_Dummy_nothing_happens_counter == 0) //if the mate stands still after 90secs the m_Dummy_nothing_happens_countershoudl get triggerd. but if not this if function turns true
							{
								//[PLANNED]: this can cause an loop wehre nothing happens..
								//maybe add some weapon changes or change m_Input.m_TargetX a bit


								m_Input.m_Direction = -1; //ye just walk untill an emergency gets called xD
								//ik pro trick but it moves the bot around
							}



							//Emergency takes over here if the bot got in a dangerous situation!
							//if (m_Core.m_Pos.y > 196 * 32 + 30) //+25 is used for the jump help and with 30 it shoudlnt get any confusuion i hope
							if (m_Core.m_Pos.y > 195 * 32 && !m_Dummy_help_no_emergency) //if the bot left the platform
							{
								m_Dummy_help_emergency = true;
							}
							if (m_Core.m_Pos.x > 479 * 32 && m_Core.m_Jumped == 0 || isFreezed)
							{
								m_Dummy_help_emergency = false;
							}

							if (m_Dummy_help_emergency)
							{
								//resett all and let emergency control all xD
								m_Input.m_Hook = 0;
								m_Input.m_Jump = 0;
								m_Input.m_Direction = 0;
								m_LatestInput.m_Fire = 0;
								m_Input.m_Fire = 0;


								if (Server()->Tick() % 20 == 0)
								{
									GameServer()->SendEmoticon(m_pPlayer->GetCID(), 1);
								}

								m_Input.m_TargetX = 0;
								m_Input.m_TargetY = -200;
								m_LatestInput.m_TargetX = 0;
								m_LatestInput.m_TargetY = -200;

								if (m_Core.m_Pos.y > 194 * 32 + 18)
								{
									m_Input.m_Jump = 1;
								}
								if (m_Core.m_Jumped >= 2)
								{
									m_Input.m_Direction = 1;
								}
							}

						}


					}
				}
				//Hammerhit with race mate till finish
				if (m_Dummy_mode23 == 0 || m_Dummy_mode23 == 2) //normal hammerhit
				{
					if (m_Core.m_Pos.x > 491 * 32)
					{
						if (m_Core.m_Pos.x <= 514 * 32 - 5)
						{
							SetWeapon(0);
						}

						CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
						if (pChr && pChr->IsAlive())
						{
							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							//just do things if unffr
							//old shit cuz he cant rls because mate is unfreeze and dont check for later rlsing hook
							//if (m_FreezeTime == 0 && pChr->m_FreezeTime > 0) //und der mate auch freeze is (damit der nich von edges oder aus dem ziel gehookt wird)
							//                  fuck the edge only stop if finish lol
							if (m_FreezeTime == 0 && pChr->m_Pos.x < 514 * 32 - 2 || m_FreezeTime == 0 && pChr->m_Pos.x > 521 * 32 + 2)
							{
								//get right hammer pos [rechte seite]
								if (pChr->m_Pos.x < 515 * 32) //wenn der mate links des ziels ist
								{
									if (m_Core.m_Pos.x > pChr->m_Pos.x + 45) //zu weit rechts von hammer position
									{
										m_Input.m_Direction = -1; //gehe links

									}
									else if (m_Core.m_Pos.x < pChr->m_Pos.x + 39) // zu weit links von hammer position
									{
										m_Input.m_Direction = 1;
									}
								}
								else //get right hammer pos [rechte seite] (wenn der mate rechts des ziels is)
								{
									if (m_Core.m_Pos.x > pChr->m_Pos.x - 45) //zu weit links von hammer position
									{
										m_Input.m_Direction = -1;

									}
									else if (m_Core.m_Pos.x < pChr->m_Pos.x - 39) // zu weit rechts von hammer position
									{
										m_Input.m_Direction = 1;
									}
								}

								//deactivate bool for hook if mate is high enough or bot is freezed (but freezed is checked somewerhe else)
								//                                                                                              NEW: just rls hook if mate is higher than bot (to prevent both falling added new ||)
								//                                                                                                                                                                                oder wenn der mate unter dem bot ist und unfreeze
								if (pChr->m_FreezeTime == 0 && pChr->m_Core.m_Vel.y > -1.5f && m_Core.m_Pos.y > pChr->m_Pos.y - 15 || pChr->m_Core.m_Vel.y > 3.4f || pChr->m_FreezeTime == 0 && pChr->m_Pos.y + 38 > m_Core.m_Pos.y || isFreezed)
								{
									m_Dummy_hh_hook = false;
								}
								//activate bool for hook if mate stands still
								if (pChr->m_Core.m_Vel.y == 0.000000f /*|| pChr->m_Core.m_Vel.y < -4.5f*/) //wenn er am boden liegt anfangen oder wenn er zu schnell nach obenfliegt bremsen
								{
									m_Dummy_hh_hook = true;
								}

								if (m_Dummy_hh_hook)
								{
									m_Input.m_Hook = 1;
								}

								//jump if too low && if mate is freeze otherwise it woudl be annoying af
								if (m_Core.m_Pos.y > 191 * 32 && pChr->m_FreezeTime > 0)
								{
									m_Input.m_Jump = 1;
								}

								//Hammer
								//if (pChr->m_Pos.y - m_Core.m_Pos.y < 7 && pChr->m_FreezeTime > 0) //wenn der abstand der beiden tees nach oben weniger is als 7 ^^
								if (pChr->m_FreezeTime > 0 && pChr->m_Pos.y - m_Core.m_Pos.y < 18) //wenn der abstand kleiner als 10 is nach oben
								{
									m_Input.m_Fire++;
									m_LatestInput.m_Fire++;
								}
							}
							else
							{
								m_Dummy_hh_hook = false; //reset hook if bot is freeze
							}


							//ReHook if mate flys to high

							if (pChr->m_Pos.y < m_Core.m_Pos.y - 40 && pChr->m_Core.m_Vel.y < -4.4f || pChr->m_Pos.y < 183 * 32)
							{
								m_Input.m_Hook = 1;
							}

							//Check for panic balance cuz all went wrong lol
							//if dummy is too much left and has no dj PANIC!
							//                                                                                                                                           New Panic Trigger: if both fall fast an the bot is on top                                    
							if (pChr->m_Pos.x < 516 * 32 && m_Core.m_Jumped >= 2 && m_Core.m_Pos.x < pChr->m_Pos.x - 5 && pChr->m_Pos.y > m_Core.m_Pos.y && m_Core.m_Pos.y > 192 * 32 && pChr->isFreezed || m_Core.m_Vel.y > 6.7f && pChr->m_Core.m_Vel.y > 7.4f && pChr->m_Pos.y > m_Core.m_Pos.y && m_Core.m_Pos.y > 192 * 32 && pChr->m_Pos.x < 516 * 32)
							{


								if (!str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "ChillerDragon") || !str_comp(Server()->ClientName(pChr->GetPlayer()->GetCID()), "ChillerDragon.*")) //only chatflame debug while racing with ChillerDragon
								{
									if (m_Dummy_sent_chat_msg == 0 && !m_Dummy_panic_balance && m_FreezeTime == 0)
									{
										int r = rand() % 16; // 0-15

										if (r == 0)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "YOU SUCK LOL!");
										}
										else if (r == 1)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "what do you do?!");
										}
										else if (r == 2)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "O M G =!! what r u triin mate?");
										}
										else if (r == 3)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "you did shit. i didnt do shit because im a bot and i am perfect.");
										}
										else if (r == 4)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "what was your plan?");
										}
										else if (r == 5)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "this looks bad! i try to balance...");
										}
										else if (r == 6)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "i think we gonna die ....  lemme try to balance");
										}
										else if (r == 7)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "what was this?");
										}
										else if (r == 8)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "you fucked it up .. let me try to save us with my balance skills.");
										}
										else if (r == 9)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "do you have lags? i dont have lags.");
										}
										else if (r == 10)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "lol.");
										}
										else if (r == 11)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "lul");
										}
										else if (r == 12)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "wtf?");
										}
										else if (r == 13)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "OMG");
										}
										else if (r == 14)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "?!");
										}
										else if (r == 15)
										{
											GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "whats going on here?!");
										}

										//GameServer()->SendEmoticon(m_pPlayer->GetCID(), 4);
										m_Dummy_sent_chat_msg = 1;
									}
								}



								m_Dummy_panic_balance = true;
							}
							if (pChr->m_FreezeTime == 0 || isFreezed || pChr->m_Pos.x > 512 * 32 + 5) //if mate gets unfreezed or dummy freezed stop balance
							{
								m_Dummy_panic_balance = false;
							}


							if (m_Dummy_panic_balance)
							{
								if (m_Core.m_Pos.x < pChr->m_Pos.x - 2) //Bot is too far left
								{
									m_Input.m_Direction = 1;
								}
								else if (m_Core.m_Pos.x > pChr->m_Pos.x) //Bot is too far right
								{
									m_Input.m_Direction = -1;
								}

								if (m_Core.m_Pos.x > pChr->m_Pos.x - 2 && m_Core.m_Pos.x < pChr->m_Pos.x && m_Core.m_Vel.x > -0.3f && m_FreezeTime == 0)
								{
									m_Input.m_Direction = 1;
									m_Input.m_Fire++;
									m_LatestInput.m_Fire++;
								}
							}


							//Go in finish if near enough
							if (m_Core.m_Vel.y < 4.4f && m_Core.m_Pos.x > 511 * 32 || m_Core.m_Vel.y < 8.4f && m_Core.m_Pos.x > 512 * 32)
							{
								if (m_Core.m_Pos.x < 514 * 32 && !m_Dummy_panic_balance)
								{
									m_Input.m_Direction = 1;
								}
							}

							//If dummy made it till finish but mate is still freeze on the left side
							//he automaiclly help. BUT if he fails the hook resett it!
							//left side                                                                                      right side
							if (m_Core.m_Pos.x > 514 * 32 - 5 && m_FreezeTime == 0 && pChr->isFreezed && pChr->m_Pos.x < 515 * 32 || m_Core.m_Pos.x > 519 * 32 - 5 && m_FreezeTime == 0 && pChr->isFreezed && pChr->m_Pos.x < 523 * 32)
							{
								if (Server()->Tick() % 70 == 0)
								{
									m_Input.m_Hook = 0;
									//GameServer()->SendEmoticon(m_pPlayer->GetCID(), 1);
								}
							}
							//if mate is too far for hook --> shotgun him
							if (m_Core.m_Pos.x > 514 * 32 - 5 && m_Core.m_Pos.x > pChr->m_Pos.x && m_Core.m_Pos.x - pChr->m_Pos.x > 8 * 32)
							{
								SetWeapon(2); //shotgun
								if (pChr->m_FreezeTime > 0 && m_FreezeTime == 0 && pChr->m_Core.m_Vel.y == 0.000000f)
								{
									m_Input.m_Fire++;
									m_LatestInput.m_Fire++;
								}
							}
							//another hook if normal hook doesnt work
							//to save mate if bot is finish
							if (m_Input.m_Hook == 0)
							{
								if (pChr->m_FreezeTime > 0 && m_FreezeTime == 0 && m_Core.m_Pos.y < pChr->m_Pos.y - 60 && m_Core.m_Pos.x > 514 * 32 - 5)
								{
									m_Input.m_Hook = 1;
									m_Input.m_Fire++;
									m_LatestInput.m_Fire++;
									if (Server()->Tick() % 10 == 0)
									{
										GameServer()->SendEmoticon(m_pPlayer->GetCID(), 1);
									}
								}
							}



							//Important dont walk of finish plattform check
							//if (m_Core.m_Vel.y < 6.4f) //Check if not falling to fast
							if (!m_Dummy_panic_balance)
							{
								if (m_Core.m_Vel.y < 6.4f && m_Core.m_Pos.x > 512 * 32 && m_Core.m_Pos.x < 515 * 32 || m_Core.m_Pos.x > 512 * 32 + 30 && m_Core.m_Pos.x < 515 * 32) //left side
								{
									m_Input.m_Direction = 1;
								}
								if (m_Core.m_Vel.y < 6.4f && m_Core.m_Pos.x > 520 * 32 && m_Core.m_Pos.x < 524 * 32 /* || too lazy rarly needed*/) //right side
								{
									m_Input.m_Direction = -1;
								}
							}


						}
					}












				}
				else if (m_Dummy_mode23 == 1) //tricky hammerhit (harder)
				{
					if (m_Core.m_Pos.x > 491 * 32)
					{
						SetWeapon(0);
						CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
						if (pChr && pChr->IsAlive())
						{
							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							//just do things if unffr
							if (m_FreezeTime == 0 && pChr->m_FreezeTime > 0) //und der mate auch freeze is (damit der nich von edges oder aus dem ziel gehookt wird)
							{
								//get right hammer pos [rechte seite]
								if (m_Core.m_Pos.x > pChr->m_Pos.x + 45)
								{
									m_Input.m_Direction = -1;
								}
								else if (m_Core.m_Pos.x < pChr->m_Pos.x + 39)
								{
									m_Input.m_Direction = 1;
								}


								//deactivate bool for hook if mate is high enough or bot is freezed (but freezed is checked somewerhe else)
								//                                                                                              NEW: just rls hook if mate is higher than bot (to prevent both falling added new ||)
								if (/*m_Core.m_Pos.y - pChr->m_Pos.y > 15 ||*/ pChr->m_FreezeTime == 0 && pChr->m_Core.m_Vel.y < -2.5f && pChr->m_Pos.y < m_Core.m_Pos.y || pChr->m_Core.m_Vel.y > 3.4f)
								{
									m_Dummy_hh_hook = false;
									//GameServer()->SendEmoticon(m_pPlayer->GetCID(), 1);
								}
								//activate bool for hook if mate stands still
								if (pChr->m_Core.m_Vel.y == 0.000000f) //wenn er am boden liegt anfangen oder wenn er zu schnell nach obenfliegt bremsen
								{
									m_Dummy_hh_hook = true;
								}



								//jump if too low && if mate is freeze otherwise it woudl be annoying af
								if (m_Core.m_Pos.y > 191 * 32 && pChr->m_FreezeTime > 0)
								{
									m_Input.m_Jump = 1;
								}

								//Hammer
								//wenn der abstand der beiden tees nach oben weniger is als 7 ^^
								if (pChr->m_FreezeTime > 0 && pChr->m_Pos.y - m_Core.m_Pos.y < 18) //wenn der abstand kleiner als 10 is nach oben
								{
									m_Input.m_Fire++;
									m_LatestInput.m_Fire++;
								}
							}
							else
							{
								m_Dummy_hh_hook = false; //reset hook if bot is freeze
														 //GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);
							}
						}
					}


					if (m_Dummy_hh_hook)
					{
						m_Input.m_Hook = 1;
					}
				}
			}


			//General bug protection resett hook in freeze
			if (isFreezed)
			{
				m_Input.m_Hook = 0; //resett hook in freeze to prevent bugs with no hooking at last part
			}

			//Leave THis LAST !!!
			//chat stuff

			if (m_Dummy_sent_chat_msg > 0 && m_Dummy_sent_chat_msg < 100)
			{
				m_Dummy_sent_chat_msg++;
			}
			else
			{
				m_Dummy_sent_chat_msg = 0;
			}
		}
		else if (m_pPlayer->m_DummyMode == 24) //new better mode 3
		{
			//########################################
			// YOUTUBE
			// 800 likes top comment omg!
			// https://www.youtube.com/watch?v=xjgd8dki_V4&google_comment_id=z13vxrwiqriytlq3023exlkr5n3sydpvs
			// 100 likes top comment omg!
			// https://www.youtube.com/watch?v=oDTO8j12CBI&google_comment_id=z12ojtqx3tmsxtq1u23exlkr5n3sydpvs
			//#######################################
			// American Ultra
			// He never died
			// watchmen
			// deadpool


			//ressettin
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			//searching friends <3
			CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
			if (pChr && pChr->IsAlive())
			{
				//suiciding

				//check for killprotection
				if (Server()->Tick() % 600 == 0)
				{
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "i survived long wow!");
					m_Dummy_survival_time++;
				}

				if (isFreezed)
				{
					if (m_Core.m_Vel.y == 0.000000f)
					{
						if (Server()->Tick() % (200 + m_Dummy_survival_time) == 0)
						{
							if (!m_Dummy_chat)
							{
								int r = rand() % 10;
								if (r == 0) //ask for help (not to often)
								{
									GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "im freeze :c");
									m_Dummy_chat = true;
								}
								else if (r == 1)
								{
									GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "help me please.");
									m_Dummy_chat = true;
								}
								else if (r == 2)
								{
									GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "help me. I promise i am not going to attack you.");
									m_Dummy_chat = true;
								}
								else if (r == 3)
								{
									GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "hellu? im freeze :(");
									m_Dummy_chat = true;
								}
								else if (r == 4)
								{
									GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "I need help. I am stuck!");
									m_Dummy_chat = true;
								}
								else
								{
									Die(m_pPlayer->GetCID(), WEAPON_SELF);
									m_Dummy_survival_time = 0;
								}
							}
							else
							{
								Die(m_pPlayer->GetCID(), WEAPON_SELF);
								m_Dummy_survival_time = 0;
							}
						}
					}
				}





				int r = rand() % 30;

				//m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				//m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
				m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x + r;
				m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y + r;

				if (pChr->m_Pos.y == m_Core.m_Pos.y)
				{
					if (pChr->m_Pos.x > m_Core.m_Pos.x + 77) //if friend is on the right of the bot
					{
						m_Input.m_Direction = 1;

					}
					else if (pChr->m_Pos.x < m_Core.m_Pos.x - 77) //if firend is on the left of the bot
					{
						m_Input.m_Direction = -1;

					}
					else
					{
						if (Server()->Tick() % 60 == 0)
						{
							GameServer()->SendEmoticon(m_pPlayer->GetCID(), 2);
						}
					}

				}
			}
			else //no pChr alive
			{
				if (isFreezed)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}
			}
		}
		//yep rip 25 too shit and doesnt compile on linux
		//else if (m_pPlayer->m_DummyMode == 25) //ChillerDraguns testy nural network lol
		//{
		//	/*
		//	######################################################
		//	#     DummyMode 25      The    FNN    Mode           #
		//	#           [FNN] == [FAKENEURALNETWORK]             #
		//	######################################################
		//	ModeStructure:
		//	
		//	* Spawn -> goto hardcodet spawn pos.x 404 * 32 + 20
		//	
		//	* Check for human interactions and save them in the var m_Dummy_nn_touched_by_humans

		//	* submodes: 0 1 2  write read_fitt read_dist

		//	* submode[0] create random values for inp_fire inp_jump inp_hook ...  and if freezed write them into a txt:
		//		if distance > highest_distance --> write in highest_distance.txt
		//		if fitness > highest_fitness --> write in highest_fitness.txt
		//		if touched && distance > highest_distance_touched --> write in highest_distance_touched.txt  (no fitness for touched)

		//	* submode[1] readhighest fitness from highest_fitness.txt

		//	* submode[2] readhighest distance from highest_distance.txt
		//	
		//	
		//	
		//	*/
		//	if (!m_Dummy_nn_ready) //first get the right start pos
		//	{
		//		m_Input.m_Hook = 0;
		//		m_Input.m_Jump = 0;
		//		m_Input.m_Direction = 0;
		//		m_LatestInput.m_Fire = 0;
		//		m_Input.m_Fire = 0;

		//		if (m_Core.m_Pos.x <= 404 * 32 + 20)
		//		{
		//			//if (m_Core.m_Vel.y == 0.000000f) //only move if speed is 0
		//			if (IsGrounded()) //pro shit xD 
		//			{
		//				if (m_Core.m_Pos.x > 403 * 32 + 20)
		//				{
		//					//if (Server()->Tick() % 7 == 0)
		//					if (m_Core.m_Vel.x < 0.04f)
		//					{
		//						m_Input.m_Direction = 1;
		//					}
		//				}
		//				else
		//				{
		//					m_Input.m_Direction = 1;
		//				}
		//			}
		//		}
		//		//if (m_Core.m_Pos.x > 404 * 32 + 19)
		//		else
		//		{
		//			if (IsGrounded() && m_Core.m_Pos.x < 404 * 32 + 22)
		//			{
		//				//right position and right speed to start
		//				m_Dummy_nn_ready = true;
		//				GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", "Found start position -> starting process");
		//			}
		//		}

		//		if (m_Dummy_nn_ready_time > 300)
		//		{
		//			GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", "Starting process failed. Get in start position took too long -> restarting...");
		//			Die(m_pPlayer->GetCID(), WEAPON_SELF);
		//		}
		//		m_Dummy_nn_ready_time++;
		//		//char aBuf[256];
		//		//str_format(aBuf, sizeof(aBuf), "time: %d", m_Dummy_nn_ready_time);
		//		//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);

		//	}
		//	else //if the bot has the right start pos start doing random stuff 
		//	{
		//		//m_Dummy_nn_write = true;
		//		/*


		//		dummy sub mode structure:

		//		old used a bool (m_Dummy_nn_write) which has to be changed manually in the source.

		//		new system uses chat command /dmm25 = dummmymodemode25 to choose submodes.
		//		submodes:
		//		0					write
		//		1					read highest fitness
		//		2					read highest distance

		//		*/

		//		//TODO: add move check here
		//		//if (isMoved blabla)
		//		//{
		//		//	m_Dummy_nn_touched_by_humans = true;
		//		//}
		//		//if (!Moving() && IsGrounded())
		//		//{
		//		//	m_aMoveID = -1;
		//		//}

		//		int m_aMoveID = -1;
		//		int Hooked = false;
		//		int PullID = -1;
		//		for (int i = 0; i < MAX_CLIENTS; i++)
		//		{
		//			CCharacter *pChar = GameServer()->GetPlayerChar(i);

		//			if (!pChar || !pChar->IsAlive() || pChar == this)
		//				continue;

		//			if (pChar->Core()->m_HookedPlayer == m_pPlayer->GetCID())
		//			{
		//				Hooked = true;
		//				m_aMoveID = i;
		//				m_Dummy_nn_touched_by_humans = true;
		//				GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "DONT TOUCH ME HOOK WTF");
		//			}
		//		}
		//		if (m_Core.m_HookState == HOOK_GRABBED)
		//		{
		//			m_Dummy_nn_touched_by_humans = true;
		//			GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "dont get in my hook -.-");
		//		}
		//		//selfmade noob code check if pChr is too near and coudl touched the bot
		//		CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
		//		if (pChr && pChr->IsAlive())
		//		{
		//			if (pChr->m_Pos.x < m_Core.m_Pos.x + 60 && pChr->m_Pos.x > m_Core.m_Pos.x - 60 && pChr->m_Pos.y < m_Core.m_Pos.y + 60 && pChr->m_Pos.y > m_Core.m_Pos.y - 60)
		//			{
		//				m_Dummy_nn_touched_by_humans = true;
		//				GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "dont touch my body with yours pls");
		//			}

		//		}






		//		m_pPlayer->m_dmm25 = 2;

		//		if (m_pPlayer->m_dmm25 == 0) //submode[0] write
		//		{
		//			//m_pPlayer->m_TeeInfos.m_Name = "writing...";
		//			//m_pPlayer->m_TeeInfos.m_ColorBody = (180 * 255 / 360);


		//			m_pPlayer->m_Dummy_nn_time++;

		//			int rand_Direction = rand() % 3 - 1; //-1 0 1
		//			int rand_Fire = rand() % 2; // 1 0
		//			int rand_Jump = rand() % 2;
		//			int rand_Hook = rand() % 2;
		//			int rand_Weapon = rand() % 4;
		//			int rand_TargetX = rand() % 401 - 200;
		//			int rand_TargetY = rand() % 401 - 200;

		//			m_Input.m_Direction = rand_Direction;
		//			m_Input.m_Jump = rand_Jump;
		//			m_Input.m_Hook = rand_Hook;
		//			m_Input.m_TargetX = rand_TargetX;
		//			m_Input.m_TargetY = rand_TargetY;
		//			m_LatestInput.m_TargetX = rand_TargetX;
		//			m_LatestInput.m_TargetY = rand_TargetY;
		//			if (rand_Weapon == 0)
		//			{
		//				SetWeapon(0); //hammer
		//			}
		//			else if (rand_Weapon == 1)
		//			{
		//				SetWeapon(1); //gun
		//			}
		//			else if (rand_Weapon == 2)
		//			{
		//				if (m_aWeapons[WEAPON_SHOTGUN].m_Got)
		//				{
		//					SetWeapon(2); //shotgun
		//				}
		//			}
		//			else if (rand_Weapon == 3)
		//			{
		//				if (m_aWeapons[WEAPON_GRENADE].m_Got)
		//				{
		//					SetWeapon(3); //grenade
		//				}
		//			}
		//			else if (rand_Weapon == 4)
		//			{
		//				if (m_aWeapons[WEAPON_RIFLE].m_Got)
		//				{
		//					SetWeapon(4); //laser
		//				}
		//			}
		//			else
		//			{
		//				char aBuf[256];
		//				str_format(aBuf, sizeof(aBuf), "Error unknown weapon:", rand_Weapon);
		//				GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);
		//			}
		//			if (rand_Fire == 1 && m_FreezeTime == 0)
		//			{
		//				m_Input.m_Fire++;
		//				m_LatestInput.m_Fire++;
		//			}



		//			char *inname = "dummy_latest_fitness.txt";
		//			static ofstream infile(inname);



		//			char aBuf[256];


		//			if (!infile)
		//			{
		//				str_format(aBuf, sizeof(aBuf), "Error reading file: %x", inname);
		//				GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);
		//				infile.close();
		//			}
		//			else
		//			{
		//				infile << rand_Direction << " " << rand_Fire << " " << rand_Jump << " " << rand_Hook << " " << rand_Weapon << " " << rand_TargetX << " " << rand_TargetY << endl;
		//			}

		//			if (m_Core.m_Vel.y == 0.000000f && m_Core.m_Vel.x < 0.01f && m_Core.m_Vel.x > -0.01f && isFreezed)
		//			{
		//				if (Server()->Tick() % 10 == 0)
		//				{
		//					GameServer()->SendEmoticon(m_pPlayer->GetCID(), 3);
		//				}



		//				if (Server()->Tick() % 40 == 0)
		//				{
		//					if (!m_Dummy_nn_touched_by_humans) //no interaction with humans --> save normal
		//					{
		//						//TODO: maybe move this somewehre in a init area
		//						//NEW read fitness and distance from file!
		//						//load fitness:
		//						{ //added this one to prevent newdefinition of vars
		//							char *load_fitness = "dummy_highest_fitness.txt";
		//							static ifstream infile(load_fitness);
		//							char aBuf[256];
		//							if (!infile)
		//							{
		//								str_format(aBuf, sizeof(aBuf), "Error loading fitness: %x", load_fitness);
		//								GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//								//infile.close();
		//							}
		//							else
		//							{

		//								str_format(aBuf, sizeof(aBuf), "succesfully loaded fitness: %x", load_fitness);
		//								//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//								if (infile >> m_pPlayer->m_Dummy_nn_highest_fitness)
		//								{

		//									str_format(aBuf, sizeof(aBuf), "successfully loaded highest fitness:  %.2f", m_pPlayer->m_Dummy_nn_highest_fitness);
		//									GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//								}
		//							}
		//							infile.close();
		//						}
		//						//load distance:
		//						{   //added this one to prevent newdefinition of vars
		//							char *load_Distance = "dummy_highest_Distance.txt";
		//							static ifstream infile(load_Distance);
		//							char aBuf[256];
		//							if (!infile)
		//							{
		//								str_format(aBuf, sizeof(aBuf), "Error loading Distance: %x", load_Distance);
		//								GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//								infile.close();
		//							}
		//							else
		//							{

		//								str_format(aBuf, sizeof(aBuf), "succesfully loaded Distance: %x", load_Distance);
		//								//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//								if (infile >> m_pPlayer->m_Dummy_nn_highest_Distance)
		//								{

		//									str_format(aBuf, sizeof(aBuf), "successfully loaded highest Distance:  %.2f", m_pPlayer->m_Dummy_nn_highest_Distance);
		//									GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//								}
		//							}
		//							infile.close();
		//						}



		//						m_pPlayer->m_Dummy_nn_latest_Distance = m_Core.m_Pos.x - 404 * 32;

		//						m_pPlayer->m_Dummy_nn_latest_fitness = m_pPlayer->m_Dummy_nn_latest_Distance / m_pPlayer->m_Dummy_nn_time;



		//						if (m_pPlayer->m_Dummy_nn_latest_fitness > m_pPlayer->m_Dummy_nn_highest_fitness)
		//						{
		//							m_pPlayer->m_Dummy_nn_highest_fitness = m_pPlayer->m_Dummy_nn_latest_fitness;



		//							std::ifstream InputFile("dummy_latest_fitness.txt"); // Open test.piko to read bits(std::ios::binary)
		//							string Content;
		//							while (!InputFile.eof()) // loop through whole file, line by line (eof == end of file)
		//							{
		//								string TempContent;
		//								std::getline(InputFile, TempContent); // Store the current line to or TempContent...

		//								Content += TempContent + "\n"; // ... then to our whole Content
		//							}

		//							InputFile.close(); // Close it to free the memory

		//							std::ofstream OutputFile("dummy_highest_fitness.txt"); // Create new File / Overwrite existing one!
		//							OutputFile << m_pPlayer->m_Dummy_nn_highest_fitness << endl;


		//							for (int i = 0; i <= Content.length(); i++)// loop through each character of array
		//								OutputFile << Content.c_str()[i]; // Write Content (.c_str() creates a char array, and we want the i-char of it to write);

		//							OutputFile.close(); // Close it to free the memory
		//						}

		//						if (m_pPlayer->m_Dummy_nn_latest_Distance > m_pPlayer->m_Dummy_nn_highest_Distance)
		//						{
		//							m_pPlayer->m_Dummy_nn_highest_Distance = m_pPlayer->m_Dummy_nn_latest_Distance;


		//							std::ifstream InputFile("dummy_latest_fitness.txt"); // Open test.piko to read bits(std::ios::binary)
		//							string Content;
		//							while (!InputFile.eof()) // loop through whole file, line by line (eof == end of file)
		//							{
		//								string TempContent;
		//								std::getline(InputFile, TempContent); // Store the current line to or TempContent...

		//								Content += TempContent + "\n"; // ... then to our whole Content
		//							}

		//							InputFile.close(); // Close it to free the memory

		//							std::ofstream OutputFile("dummy_highest_Distance.txt"); // Create new File / Overwrite existing one!
		//							OutputFile << m_pPlayer->m_Dummy_nn_highest_Distance << endl;


		//							for (int i = 0; i <= Content.length(); i++)// loop through each character of array
		//								OutputFile << Content.c_str()[i]; // Write Content (.c_str() creates a char array, and we want the i-char of it to write);

		//							OutputFile.close(); // Close it to free the memory
		//						}

		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", "+-----------------------+");
		//						str_format(aBuf, sizeof(aBuf), "Pos.x: %.2f", m_Core.m_Pos.x / 32);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						str_format(aBuf, sizeof(aBuf), "Distance: %.2f Time: %d", m_Core.m_Pos.x - 404 * 32, m_pPlayer->m_Dummy_nn_time);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						str_format(aBuf, sizeof(aBuf), "Finished with fitness: %f", m_pPlayer->m_Dummy_nn_latest_fitness);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						str_format(aBuf, sizeof(aBuf), "HighestFitness: %.2f  HighestDistance: %.2f", m_pPlayer->m_Dummy_nn_highest_fitness, m_pPlayer->m_Dummy_nn_highest_Distance);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", "+-----------------------+");

		//						m_pPlayer->m_Dummy_nn_time = 0;
		//						Die(m_pPlayer->GetCID(), WEAPON_SELF);
		//					}
		//					else //if the bot got touched by humans save the run in touched by humans stats xD
		//					{
		//						//load distance (touched):
		//						{   //added this one to prevent newdefinition of vars
		//							char *load_Distance_t = "dummy_highest_Distance_touched.txt";
		//							static ifstream infile(load_Distance_t);
		//							char aBuf[256];
		//							if (!infile)
		//							{
		//								str_format(aBuf, sizeof(aBuf), "Error loading Distance touched: %x", load_Distance_t);
		//								GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//								infile.close();
		//							}
		//							else
		//							{

		//								str_format(aBuf, sizeof(aBuf), "succesfully loaded Distance touched: %x", load_Distance_t);
		//								//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//								if (infile >> m_pPlayer->m_Dummy_nn_highest_Distance_touched)
		//								{

		//									str_format(aBuf, sizeof(aBuf), "successfully loaded highest Distance touched:  %.2f", m_pPlayer->m_Dummy_nn_highest_Distance);
		//									GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//								}
		//							}
		//							infile.close();
		//						}


		//						m_pPlayer->m_Dummy_nn_latest_Distance = m_Core.m_Pos.x - 404 * 32;


		//						if (m_pPlayer->m_Dummy_nn_latest_Distance > m_pPlayer->m_Dummy_nn_highest_Distance_touched)
		//						{
		//							m_pPlayer->m_Dummy_nn_highest_Distance_touched = m_pPlayer->m_Dummy_nn_latest_Distance;


		//							std::ifstream InputFile("dummy_latest_fitness.txt"); 
		//							string Content;
		//							while (!InputFile.eof()) 
		//							{
		//								string TempContent;
		//								std::getline(InputFile, TempContent); 

		//								Content += TempContent + "\n"; 
		//							}

		//							InputFile.close();

		//							std::ofstream OutputFile("dummy_highest_Distance_touched.txt"); 
		//							OutputFile << m_pPlayer->m_Dummy_nn_highest_Distance_touched << endl;


		//							for (int i = 0; i <= Content.length(); i++)// loop through each character of array
		//								OutputFile << Content.c_str()[i]; // Write Content (.c_str() creates a char array, and we want the i-char of it to write);

		//							OutputFile.close(); // Close it to free the memory
		//						}

		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", "+-----------------------+");
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", "[TOUCHED]");
		//						str_format(aBuf, sizeof(aBuf), "Pos.x[T]: %.2f", m_Core.m_Pos.x / 32);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						str_format(aBuf, sizeof(aBuf), "Distance[T]: %.2f Time: %d", m_Core.m_Pos.x - 404 * 32, m_pPlayer->m_Dummy_nn_time);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						str_format(aBuf, sizeof(aBuf), "Finished with fitness[T]: %f", m_pPlayer->m_Dummy_nn_latest_fitness);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						str_format(aBuf, sizeof(aBuf), "HighestFitness: %.2f  HighestDistance: %.2f HighestDistance[T]: %.2f", m_pPlayer->m_Dummy_nn_highest_fitness, m_pPlayer->m_Dummy_nn_highest_Distance, m_pPlayer->m_Dummy_nn_highest_Distance_touched);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", "+-----------------------+");

		//						m_pPlayer->m_Dummy_nn_time = 0;
		//						Die(m_pPlayer->GetCID(), WEAPON_SELF);
		//					}
		//				}
		//			}
		//		}
		//		else if (m_pPlayer->m_dmm25 == 1) //submode[1] read fitness
		//		{
		//			//m_pPlayer->m_TeeInfos.m_Name = "reading fitness...";
		//			m_pPlayer->m_TeeInfos.m_ColorBody = (300 * 255 / 360);

		//			char *inname = "dummy_highest_fitness.txt";
		//			static ifstream infile(inname);


		//			char aBuf[256];


		//			if (!infile)
		//			{
		//				str_format(aBuf, sizeof(aBuf), "Error reading file: %x", inname);
		//				GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);
		//				infile.close();
		//			}
		//			else
		//			{
		//				str_format(aBuf, sizeof(aBuf), "Succesfully opend file: %x", inname);
		//				GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);

		//				static bool skipped = false;
		//				int latest_value;
		//				if (!skipped)
		//				{
		//					infile >> latest_value;
		//					skipped = true;
		//				}

		//				//int a, b, c;
		//				int rand_Direction, rand_Fire, rand_Jump, rand_Hook, rand_Weapon, rand_TargetX, rand_TargetY;
		//				if (infile >> rand_Direction >> rand_Fire >> rand_Jump >> rand_Hook >> rand_Weapon >> rand_TargetX >> rand_TargetY)
		//				{
		//					// process pair (a,b,c)
		//					str_format(aBuf, sizeof(aBuf), "inp:  %d | %d | %d | %d | %d | %d | %d", rand_Direction, rand_Fire, rand_Jump, rand_Hook, rand_Weapon, rand_TargetX, rand_TargetY);
		//					GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);

		//					m_Input.m_Direction = rand_Direction;
		//					m_Input.m_Jump = rand_Jump;
		//					m_Input.m_Hook = rand_Hook;
		//					m_Input.m_TargetX = rand_TargetX;
		//					m_Input.m_TargetY = rand_TargetY;
		//					m_LatestInput.m_TargetX = rand_TargetX;
		//					m_LatestInput.m_TargetY = rand_TargetY;
		//					if (rand_Weapon == 0)
		//					{
		//						SetWeapon(0); //hammer
		//					}
		//					else if (rand_Weapon == 1)
		//					{
		//						SetWeapon(1); //gun
		//					}
		//					else if (rand_Weapon == 2)
		//					{
		//						if (m_aWeapons[WEAPON_SHOTGUN].m_Got)
		//						{
		//							SetWeapon(2); //shotgun
		//						}
		//					}
		//					else if (rand_Weapon == 3)
		//					{
		//						if (m_aWeapons[WEAPON_GRENADE].m_Got)
		//						{
		//							SetWeapon(3); //grenade
		//						}
		//					}
		//					else if (rand_Weapon == 4)
		//					{
		//						if (m_aWeapons[WEAPON_RIFLE].m_Got)
		//						{
		//							SetWeapon(4); //laser
		//						}
		//					}
		//					else
		//					{
		//						str_format(aBuf, sizeof(aBuf), "Error unknown weapon:", rand_Weapon);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);
		//					}
		//					if (rand_Fire == 1 && m_FreezeTime == 0)
		//					{
		//						m_Input.m_Fire++;
		//						m_LatestInput.m_Fire++;
		//					}

		//				}
		//				else
		//				{
		//					static bool say_end = false;

		//					if (!say_end)
		//					{
		//						GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "finished reading fitness -> closing file");
		//						//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "closing file.");
		//						infile.close();
		//					}
		//				}


		//				//str_format(aBuf, sizeof(aBuf), "value:  %d  %d  %d", a, b, c);
		//				//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);
		//			}

		//		}
		//		else if (m_pPlayer->m_dmm25 == 2) //submode[2] read distance
		//		{
		//			//m_pPlayer->m_TeeInfos.m_Name = "reading distance...";
		//			m_pPlayer->m_TeeInfos.m_ColorBody = (20 * 255 / 360);

		//			char *inname = "dummy_highest_Distance.txt";
		//			static ifstream infile(inname);


		//			char aBuf[256];


		//			if (!infile)
		//			{
		//				str_format(aBuf, sizeof(aBuf), "Error reading file: %x", inname);
		//				GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);
		//				infile.close();
		//			}
		//			else
		//			{
		//				str_format(aBuf, sizeof(aBuf), "Succesfully opend file: %x", inname);
		//				//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);

		//				static bool skipped = false;
		//				int latest_value;
		//				if (!skipped)
		//				{
		//					infile >> latest_value;
		//					skipped = true;
		//				}

		//				//int a, b, c;
		//				int rand_Direction, rand_Fire, rand_Jump, rand_Hook, rand_Weapon, rand_TargetX, rand_TargetY;
		//				if (infile >> rand_Direction >> rand_Fire >> rand_Jump >> rand_Hook >> rand_Weapon >> rand_TargetX >> rand_TargetY)
		//				{
		//					// process pair (a,b,c)
		//					str_format(aBuf, sizeof(aBuf), "inp:  %d | %d | %d | %d | %d | %d | %d", rand_Direction, rand_Fire, rand_Jump, rand_Hook, rand_Weapon, rand_TargetX, rand_TargetY);
		//					//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);

		//					m_Input.m_Direction = rand_Direction;
		//					m_Input.m_Jump = rand_Jump;
		//					m_Input.m_Hook = rand_Hook;
		//					m_Input.m_TargetX = rand_TargetX;
		//					m_Input.m_TargetY = rand_TargetY;
		//					m_LatestInput.m_TargetX = rand_TargetX;
		//					m_LatestInput.m_TargetY = rand_TargetY;
		//					if (rand_Weapon == 0)
		//					{
		//						SetWeapon(0); //hammer
		//					}
		//					else if (rand_Weapon == 1)
		//					{
		//						SetWeapon(1); //gun
		//					}
		//					else if (rand_Weapon == 2)
		//					{
		//						if (m_aWeapons[WEAPON_SHOTGUN].m_Got)
		//						{
		//							SetWeapon(2); //shotgun
		//						}
		//					}
		//					else if (rand_Weapon == 3)
		//					{
		//						if (m_aWeapons[WEAPON_GRENADE].m_Got)
		//						{
		//							SetWeapon(3); //grenade
		//						}
		//					}
		//					else if (rand_Weapon == 4)
		//					{
		//						if (m_aWeapons[WEAPON_RIFLE].m_Got)
		//						{
		//							SetWeapon(4); //laser
		//						}
		//					}
		//					else
		//					{
		//						str_format(aBuf, sizeof(aBuf), "Error unknown weapon:", rand_Weapon);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);
		//					}
		//					if (rand_Fire == 1 && m_FreezeTime == 0)
		//					{
		//						m_Input.m_Fire++;
		//						m_LatestInput.m_Fire++;
		//					}

		//				}
		//				else
		//				{
		//					GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", "Finished reading distance -> closing file");
		//					infile.close();

		//					static bool print_debug = true;

		//					if (print_debug)
		//					{
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", "+-----------------------+");
		//						str_format(aBuf, sizeof(aBuf), "Pos.x: %.2f", m_Core.m_Pos.x / 32);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						str_format(aBuf, sizeof(aBuf), "Distance: %.2f Time: %d", m_Core.m_Pos.x - 404 * 32, m_pPlayer->m_Dummy_nn_time);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						str_format(aBuf, sizeof(aBuf), "Finished with fitness: %f", m_pPlayer->m_Dummy_nn_latest_fitness);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						str_format(aBuf, sizeof(aBuf), "HighestFitness: %.2f  HighestDistance: %.2f", m_pPlayer->m_Dummy_nn_highest_fitness, m_pPlayer->m_Dummy_nn_highest_Distance);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", aBuf);
		//						GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "FNN", "+-----------------------+");

		//						print_debug = false;
		//					}



		//				}
		//				//str_format(aBuf, sizeof(aBuf), "value:  %d  %d  %d", a, b, c);
		//				//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);
		//			}
		//		}
		//		else
		//		{
		//			m_pPlayer->m_dmm25 = 0;
		//		}
		//	}



		//}
		else if (m_pPlayer->m_DummyMode == 26) //BlmapChill blocker spawn right area
		{
			//rest dummy (zuruecksetzten)
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			if (m_Core.m_Pos.x < 454 * 32) //kill wenn in tele links am spawn
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}
			if (m_Core.m_Pos.y < 78 * 32) //kill wenn zu hoch
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF); 
			}
			if (m_Core.m_Pos.y > 89 * 32 - 2 && m_Core.m_Pos.x < 493 * 32) // touched freeze floor
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}
			if (m_Core.m_Pos.x > 493 * 32 && m_Core.m_Pos.x < 507 * 32 && m_Core.m_Pos.y > 86 * 32 - 5) //touched ground in flybot tunnel
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}
			if (m_Core.m_Pos.x < 493 * 32 && m_Core.m_Vel.x < 0.3f && m_Core.m_Vel.y == 0.000000f && isFreezed) //wenn er irgendwo im freeze stecken bleibt
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}


			//Movement to block area:
			if (m_Core.m_Pos.x < 506 * 32)
			{
				m_Input.m_Direction = 1;
				if (m_Core.m_Pos.x < 469 * 32) //im spawn bereich
				{
					//bot schaut auf den boden zum boosten
					m_Input.m_TargetX = 158;
					m_Input.m_TargetY = 32;
					if (Server()->Tick() % 4 == 0)
					{
					}
					else
					{
						m_Input.m_Hook = 1;
					}
				}

				if (m_Core.m_Pos.y > 84 * 32 && m_Core.m_Pos.x < 480 * 32) //if bot is to low 
				{
					m_Input.m_TargetX = -195;
					m_Input.m_TargetY = -192;
					if (m_Core.m_Vel.x > 0.0f)
					m_Input.m_Hook = 1;
				}

				if (m_Core.m_Pos.x > 483 * 32 && m_Core.m_Pos.x < 490 * 32) //kurz form eintritt in den tunnel hook nochmal rein
				{
					if (m_Core.m_Vel.y < 6.3f) //if the bot has speed up
					{
						//---> hook down
						m_Input.m_TargetX = 70;
						m_Input.m_TargetY = 100;
						m_Input.m_Hook = 1;
					}
					else if (m_Core.m_Vel.y > 6.3f) //if the bot has speed down
					{
						//---> hook up
						m_Input.m_TargetX = 80;
						m_Input.m_TargetY = -150;
						m_Input.m_Hook = 1;
					}
					else //if the bot has not enough speed hook down/up depending on position
					{
						if (m_Core.m_Pos.y <= 82 * 32) //highest pos
						{
							m_Input.m_TargetX = 50;
							m_Input.m_TargetY = -50;
							m_Input.m_Hook = 1;
						}
						else //others
						{
							m_Input.m_TargetX = 10;
							m_Input.m_TargetY = -150;
							m_Input.m_Hook = 1;
						}
					}
				}

				if (m_Core.m_Pos.y > 87 * 32 - 15) // if bot is close freeze low
				{
					m_Input.m_Jump = 1;
				}

				//Flybotty stuff
				if (m_Core.m_Pos.x > 494 * 32)
				{
					m_Input.m_TargetX = 0;
					m_Input.m_TargetY = -190;
					if (m_Core.m_Pos.y > 85 * 32 - 2) //normal überm freeze jiggln
					{
						m_Input.m_Hook = 1;
					}

					if (m_Core.m_Pos.y > 82 * 32 + 10 && m_Core.m_Vel.y > 4.5f) //wenn der bot zu schnell fällt hooke frühzeitig
					{
						m_Input.m_Hook = 1;
					}

					if (m_Core.m_Pos.y < 82 * 32 && m_Core.m_Vel.y < 5.4f) //wenn der bot zu schnell nach oben fliegt und zu weit oben ist
					{
						m_Input.m_TargetX = 0;
						m_Input.m_TargetY = 190;
						m_Input.m_Hook = 1;
					}
					
					//Shit bot kills him self
					//if (m_Core.m_Pos.y < 85 * 32 + 10 && m_Core.m_Vel.y < -6.8f) //wenn der bot viel zu schnell nach oben fliegt reagier schneller
					//{
					//	m_Input.m_TargetX = 0;
					//	m_Input.m_TargetY = 190;
					//	m_Input.m_Hook = 1;
					//}
				}
		
			}

		}
		else if (m_pPlayer->m_DummyMode == 27) //BlmapChill test dummydrag bot (special edge hook train area left on old spawn)
		{
			//rest dummy 
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			//goto old spawn
			if (m_Core.m_Pos.x > 444 * 32)
			{
				if (m_Core.m_Pos.x > 469 * 32)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}

				if (m_Core.m_Pos.x > 80 * 32)
				{
					m_Input.m_Direction = -1;
					if (Server()->Tick() % 10 == 0)
					{
						m_Input.m_Jump = 1;
					}
				}
			}

			//if old spawn goto tele (edgehooktrain area)
			if (m_Core.m_Pos.y < 38 * 32 && m_Core.m_Pos.x < 38 * 32)
			{
				//selfkill
				//hardcodet selfkills
				if (m_Core.m_Pos.y > 34 * 32 + 30 || m_Core.m_Pos.x > 31 * 32 - 10)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}
				//dynamic selfs
				if (m_Core.m_Vel.y == 0.000000f && m_Core.m_Vel.x < 0.01f && m_Core.m_Vel.x > -0.01f && isFreezed)
				{
					if (Server()->Tick() % 20 == 0)
					{
						GameServer()->SendEmoticon(m_pPlayer->GetCID(), 3);
					}

					if (Server()->Tick() % 90 == 0)
					{
						Die(m_pPlayer->GetCID(), WEAPON_SELF);

					}
				}

				m_Input.m_Direction = -1;

				if (m_Core.m_Pos.x < 17 * 32 && m_Core.m_Pos.x > 17 * 32 - 30 || m_Core.m_Pos.x < 5 * 32 && m_Core.m_Pos.x > 5 * 32 - 30)
				{
					m_Input.m_Jump = 1;
				}

			}

			//if destiny area (edgehooktrainarea)
			if (m_Core.m_Pos.y > 31 * 32 && m_Core.m_Pos.x > 188 * 32 && m_Core.m_Pos.y < 120 * 32 && m_Core.m_Pos.x < 300 * 32)
			{
				//Selfkills
				if (m_Core.m_Pos.y > 104 * 32)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}
				if (m_Core.m_Pos.x > 213 * 32 && m_Core.m_Pos.y > 99 * 32 + 31)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}



				/*
				STRUCTURE:

				if bottom_area
				else if top_area
				else mid_area
				
				
				*/
				//bottom_area
				if (m_Core.m_Pos.y > 90 * 32)
				{
					if (m_FreezeTime == 0)
					{
						//if (m_Core.m_Pos.x < 217 * 32)
						if (m_Core.m_Pos.x < 210 * 32)
						{
							m_Input.m_Direction = 1;
						}
						if (m_Core.m_Pos.x > 209 * 32 + 20) //didnt add a limit because the dummy doesnt need jump agian until he left the area and the if loop
						{
							m_Input.m_Jump = 1;
						}
						if (m_Core.m_Pos.x < 208 * 32)
						{
							SetWeapon(3);
							m_Input.m_TargetX = -80;
							m_Input.m_TargetY = 40;
							m_LatestInput.m_TargetX = -80;
							m_LatestInput.m_TargetY = 40;


							if (m_Core.m_Vel.x > 0.7f && m_FreezeTime == 0)
							{
								m_Input.m_Fire++;
								m_LatestInput.m_Fire++;
							}
						}
						if (m_Core.m_Pos.x > 216 * 32) //switch to shotgun
						{
							SetWeapon(2);
						}
						if (m_Core.m_Pos.x > 217 * 32) //schwung hook
						{
							m_Input.m_TargetX = 80;
							m_Input.m_TargetY = -20; //old 0
							m_LatestInput.m_TargetX = 80;
							m_LatestInput.m_TargetY = -20; //old 0

							//if (m_Core.m_Pos.y > 93 * 32 || m_Core.m_Pos.x > 223 * 32)
							if (m_Core.m_Pos.y > 94 * 32 + 20 || m_Core.m_Pos.x > 223 * 32)
							{
								m_Input.m_Hook = 1;
							}
						}
						if (m_Core.m_Pos.x > 217 * 32 + 1) //schwung direction
						{
							m_Input.m_Direction = 1;
							
							if (m_Core.m_Pos.x > 224 * 32 && m_Core.m_Pos.y < 93 * 32)
							{
								m_Input.m_Direction = -1;
							}
						}
						//schwung release hook
						if (m_Core.m_Pos.x > 225 * 32 && m_Core.m_Pos.y < 93 * 32 && m_Core.m_Vel.x < -2.4f)
						{
							m_Input.m_Hook = 0;
						}
						//hook 2nd time to get the last boost
						if (m_Core.m_Pos.y < 92 * 32 - 10)
						{
							m_Input.m_TargetX = -20;
							m_Input.m_TargetY = -80;
							m_LatestInput.m_TargetX = -20;
							m_LatestInput.m_TargetY = -80;
						}
						if (m_Core.m_Pos.x < 226 * 32 && m_Core.m_Vel.x < -2.5f)
						{
							m_Input.m_TargetX = -10;
							m_Input.m_TargetY = -80;
							m_LatestInput.m_TargetX = -10;
							m_LatestInput.m_TargetY = -80;
							m_Input.m_Fire++;
							m_LatestInput.m_Fire++;
						}
					}
				}
				else if (m_Core.m_Pos.y < 84 * 32) //top_area
				{
					//Flybot new
					if (m_Core.m_Pos.x < 246 * 32)
					{
						m_Input.m_Direction = 1;
						if (m_Core.m_Pos.x < 240 * 32)
						{
							m_Input.m_Jump = 1;
						}
					}
					else if (m_Core.m_Pos.x > 249 * 32 && m_Core.m_Vel.x > 0.00002f)
					{
						m_Input.m_Direction = -1;
					}

					if (m_Core.m_Pos.x > 251 * 32 + 20)
					{
						m_Input.m_Direction = -1;
					}

					if (m_Core.m_Vel.y > 0.001f)
					{
						m_Input.m_TargetX = 300;
						m_Input.m_TargetY = -40;
						m_LatestInput.m_TargetX = 300;
						m_LatestInput.m_TargetY = -40;


						m_Input.m_Hook = 1;
					}

					if (m_Core.m_Pos.y > 80 * 32)
					{
						m_Input.m_Hook = 1;
					}

					//FLybOt old
					//if (m_Core.m_Pos.x < 249 * 32)
					//{
					//	m_Input.m_Direction = 1;
					//	if (m_Core.m_Pos.x < 240 * 32)
					//	{
					//		m_Input.m_Jump = 1;
					//	}
					//}
					//else if (m_Core.m_Pos.x > 250 * 32)
					//{
					//	m_Input.m_Direction = -1;
					//}

				
					//if (m_Core.m_Pos.x < 254 * 32 - 40 && m_Core.m_Pos.y > 76 * 32)
					//{
					//	m_Input.m_TargetX = 300;
					//	m_Input.m_TargetY = -30 - m_Dummy_panic_correction;
					//	m_LatestInput.m_TargetX = 300;
					//	m_LatestInput.m_TargetY = -30 - m_Dummy_panic_correction;

					//	m_Input.m_Hook = 1;
					//}

					////Check for panic xD
					//if (m_Core.m_Pos.y > 80 * 32 || m_Core.m_Pos.x > 251 * 32)
					//{
					//	m_Dummy_panic_correction++;
					//}
					////Check for rest panic cuz all gud
					//if (m_Core.m_Pos.y < 78 * 32 && m_Core.m_Pos.x < 250 * 32)
					//{
					//	m_Dummy_panic_correction = 0;
					//}
					////Check for super panic
					//int super_panic;
					//if (super_panic != 1 || super_panic != 2)
					//{
					//	super_panic = 0;
					//}

					//if (m_Core.m_Vel.x > 4.4f && m_Core.m_Pos.x > 251 * 32 || m_Core.m_Vel.y > 4.4f && m_Core.m_Pos.y > 77 * 32)
					//{
					//	if (super_panic != 2)
					//	super_panic = 1;
					//}

					//if (m_Core.m_Vel.x < 1.4f && m_Core.m_Vel.y < 1.4f)
					//{
					//	super_panic = 0;
					//}


					//if (super_panic == 1)
					//{
					//	m_Input.m_Hook = 0;
					//	super_panic = 2;
					//}
					//else if (super_panic == 2)
					//{
					//	m_Input.m_TargetX = 300;
					//	m_Input.m_TargetY = -50;
					//	m_LatestInput.m_TargetX = 300;
					//	m_LatestInput.m_TargetY = -50;
					//	m_Input.m_Hook = 1;
					//}

					//CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
					//if (pChr && pChr->IsAlive())
					//{
					//}

				}
				else //mid_area
				{
					SetWeapon(3); //grenade
					m_Input.m_TargetX = -30;
					m_Input.m_TargetY = 390;
					m_LatestInput.m_TargetX = -30;
					m_LatestInput.m_TargetY = 390;

					if (m_Core.m_Pos.x > 222 * 32 && m_Core.m_Vel.x < 9.8f)
					{
						m_Dummy_get_speed = true;
					}

					if (m_Dummy_get_speed)
					{
						m_Input.m_Direction = -1;
						if (m_Core.m_Pos.x < 219 * 32)
						{
							m_Dummy_get_speed = false;
						}
					}
					else
					{
						m_Input.m_Direction = 1;
					}

					//Rocketjump:
					if (m_Core.m_Pos.x > 225 * 32 && !m_Dummy_get_speed)
					{
						m_Input.m_Jump = 1;
						if (m_Core.m_Vel.y < -0.3f)
						{
							m_Input.m_Fire++;
							m_LatestInput.m_Fire++;
						}
					}

				}
			}

		}
		else if (m_pPlayer->m_DummyMode == 28)  //ChillBlock5 blmapv3 1o1 mode
		{
			//rest dummy 
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;
			//tele in area all the time
			if (m_Core.m_Pos.y > 40 * 32)
			{
				m_Core.m_Pos.y = 33 * 32;
				m_Core.m_Pos.x = 107 * 32;
			}



			CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true); 
			if (pChr && pChr->IsAlive())
			{

				m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
				m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

				//########################################
				//Worst hammer switch code eu west rofl! #
				//########################################
				//switch to hammer if enemy is near enough
				if (pChr->m_Pos.x > m_Core.m_Pos.x + 130)
				{
					//default is gun
					SetWeapon(1);
				}
				else if (pChr->m_Pos.x < m_Core.m_Pos.x - 130)
				{
					//default is gun
					SetWeapon(1);
				}
				else
				{
					//switch to hammer if enemy is near enough
					if (pChr->m_Pos.y > m_Core.m_Pos.y + 130)
					{
						//default is gun
						SetWeapon(1);
					}
					else if (pChr->m_Pos.y < m_Core.m_Pos.y - 130)
					{
						//default is gun
						SetWeapon(1);
					}
					else
					{
						//near --> hammer
						SetWeapon(0);
					}
				}

				//Starty movement
				if (m_Core.m_Pos.x < 112 * 32 && m_Core.m_Pos.y > 31 * 32 && pChr->m_Pos.y > 31 * 32 && pChr->m_Pos.x > 121 * 32 && IsGrounded() && pChr->IsGrounded())
				{
					m_Input.m_Jump = 1;
				}
				if (m_Core.m_Pos.x < 112 * 32 && pChr->m_Pos.x > 30 * 32 && pChr->m_Pos.x > 121 * 32)
				{
					m_Input.m_Direction = 1;
				}



				//important freeze doges leave them last!:

				//freeze prevention mainpart down right
				if (m_Core.m_Pos.x > 120 * 32 && m_Core.m_Pos.x < 124 * 32 && m_Core.m_Pos.y > 30 * 32)
				{
					m_Input.m_Jump = 1;
					m_Input.m_Hook = 1;
					if (Server()->Tick() % 20 == 0)
					{
						m_Input.m_Hook = 0;
					}
					m_Input.m_Direction = 1;
					m_Input.m_TargetX = 200;
					m_Input.m_TargetY = 80;
				}

				//freeze prevention mainpart down left
				if (m_Core.m_Pos.x > 110 * 32 && m_Core.m_Pos.x < 114 * 32 && m_Core.m_Pos.y > 30 * 32)
				{
					m_Input.m_Jump = 1;
					m_Input.m_Hook = 1;
					if (Server()->Tick() % 20 == 0)
					{
						m_Input.m_Hook = 0;
					}
					m_Input.m_Direction = -1;
					m_Input.m_TargetX = -200;
					m_Input.m_TargetY = 80;
				}

				//Freeze prevention top left
				if (m_Core.m_Pos.x < 114 * 32 && m_Core.m_Pos.y < 23 * 32 && m_Core.m_Pos.x > 110 * 32 - 10)
				{
					m_Input.m_Direction = -1;
					m_Input.m_Hook = 1;
					if (Server()->Tick() % 20 == 0)
					{
						m_Input.m_Hook = 0;
					}
					m_Input.m_TargetX = -200;
					m_Input.m_TargetY = -87;
					if (m_Core.m_Pos.y > 19 * 32 + 20)
					{
						m_Input.m_TargetX = -200;
						m_Input.m_TargetY = -210;
					}
				}

				//Freeze prevention top right
				if (m_Core.m_Pos.x < 125 * 32 + 10 && m_Core.m_Pos.y < 23 * 32 && m_Core.m_Pos.x > 120 * 32)
				{
					m_Input.m_Direction = 1;
					m_Input.m_Hook = 1;
					if (Server()->Tick() % 20 == 0)
					{
						m_Input.m_Hook = 0;
					}
					m_Input.m_TargetX = 200;
					m_Input.m_TargetY = -87;
					if (m_Core.m_Pos.y > 19 * 32 + 20)
					{
						m_Input.m_TargetX = 200;
						m_Input.m_TargetY = -210;
					}
				}

				//Freeze prevention mid
				if (m_Core.m_Pos.x > 116 * 32 - 7 && m_Core.m_Pos.x < 119 * 32 + 7)
				{
					if (m_Core.m_Vel.x < 0.0f)
					{
						m_Input.m_Direction = -1;
					}
					else
					{
						m_Input.m_Direction = 1;
					}

					if (m_Core.m_Pos.y > 29 * 32 - 1 && IsGrounded() == false)
					{
						m_Input.m_Jump = 1;
						if (m_Core.m_Jumped > 2) //no jumps == rip   --> panic hook
						{
							m_Input.m_Hook = 1;
							if (Server()->Tick() % 15 == 0)
							{
								m_Input.m_Hook = 0;
							}
						}
					}
				}

				//Freeze prevention left 
				if (m_Core.m_Pos.x < 102 * 32 || m_Core.m_Pos.x < 104 * 32 && m_Core.m_Vel.x < -8.4f)
				{
					m_Input.m_Direction = 1;
				}
				//Freeze prevention right
				if (m_Core.m_Pos.x > 133 * 32 || m_Core.m_Pos.x > 130 * 32 && m_Core.m_Vel.x > 8.4f)
				{
					m_Input.m_Direction = -1;
				}
			}

		}
		else if (m_pPlayer->m_DummyMode == 29) //mode 18 (tryhardwayblocker cb5)    with some more human wayblock style not so try hard a cool chillblock5 blocker mode
		{
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0; //this is 29 only the mode 18 had no jump resett hope it works ... it shoudl omg
			//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "HALLO ICH BIN 29!");

			//Check ob dem bot langweilig geworden is :)


			if (m_Dummy_bored_counter > 2)
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{

				}
				else //no ruler alive 
				{
					m_Dummy_lock_bored = true;
				}
			}
			else
			{
				m_Dummy_lock_bored = false;
			}

				
			if (m_Dummy_lock_bored)
			{
				if (m_Core.m_Pos.x < 429 * 32 && IsGrounded())
				{
					m_Dummy_bored = true;
					//static bool test = false;

					//if (!test)
					//{
					//	GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "bored");
					//	test = true;
					//}
				}
			}


			/*
			####################################################
			#   I M P O R T A N T    I N F O R M A T I O N S   #
			####################################################

			DummyMode 29 is a very special mode cause it uses the mode18 as base
			and mode18 is for now the biggest mode ever made so this code is a huge mess
			so mode29 uses a lot of mode18 vars

			Mode18 is a tryhard ruler he wayblocks as good as he can and blocks if somebody manages to get in his area

			Mode29 is a blocker which is not dat tryhard he doesnt wayblock and does more random stuff and trys freezeblock tricks 







			BRAND NEW STRUCTURE!
			WELCOME TO 18's SPECIAL MODE-CEPTION!

			dummymode 18 hase his own modes in the mode lol


			:::::::::::::::::::::
			dummymode29 modes
			:::::::::::::::::::::
			mode:         desc:
			0					Main mode
			1					attack mode (if ruler spot is ruled and bot is in tunnel)
			2                   different wayblock mode
			3					special defend mode
			4                   (PLANNED) 1on1 mode with counting in chat and helping




			dummymode29 code structure:
			- Check for activating other modes
			- big if clause with all modes

			*/


			//Check for activating other modes

			//Check mode 1 [Attack from tunnel wayblocker]
			//man könnte das auch mit m_Dummy_happy abfragen aber mich nich ganz so viel sinn
			if (m_Core.m_Pos.y > 214 * 32 && m_Core.m_Pos.x > 424 * 32)
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRulerWB(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{

					//Wenn der bot im tunnel ist und ein Gegner im RulerWB bereich
					m_Dummy_mode18 = 1;
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Wayblocker gesichtet");

				}
			}
			else if (m_Dummy_bored)
			{
				m_Dummy_mode18 = 2;
			}
			else if (m_Dummy_special_defend) //Check mode 3 [Attack from tunnel wayblocker]
			{
				m_Dummy_mode18 = 3;
			}
			else
			{
				m_Dummy_mode18 = 0; //change to main mode
			}




			//Modes:

			if (m_Dummy_mode18 == 3) //special defend mode
			{
				//testy wenn der dummy in den special defend mode gesetzt wird pusht das sein adrenalin und ihm is nicht mehr lw
				m_Dummy_bored_counter = 0;

				CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{

					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;



					m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

					//rest on tick
					m_Input.m_Hook = 0;
					m_Input.m_Jump = 0;
					m_Input.m_Direction = 0;
					m_LatestInput.m_Fire = 0;
					m_Input.m_Fire = 0;
					SetWeapon(1); //gun verwenden damit auch erkannt wird wann der mode getriggert wird


					if (pChr->m_FreezeTime == 0)
					{
						//wenn der gegner doch irgendwie unfreeze wird übergib an den main mode und lass den notstand das regeln
						m_Dummy_special_defend = false;
						m_Dummy_special_defend_attack = false;
					}
					//mode18 sub mode 3
					//Main code:
					//warte bis der gegner auf den boden geklatscht ist
					//dann werf ihn rechts runter

					if (pChr->m_Core.m_Vel.y > -0.9f && pChr->m_Pos.y > 211 * 32)
					{
						//wenn der gegner am boden liegt starte angriff
						m_Dummy_special_defend_attack = true;

						//start jump
						m_Input.m_Jump = 1;
					}


					if (m_Dummy_special_defend_attack)
					{
						if (m_Core.m_Pos.x - pChr->m_Pos.x < 50) //wenn der gegner nah genung is mach dj
						{
							m_Input.m_Jump = 1;
						}

						if (pChr->m_Pos.x < m_Core.m_Pos.x)
						{
							m_Input.m_Hook = 1;
						}
						else //wenn der gegner weiter rechts als der bot is lass los und übergib an main deine arbeit ist hier getahen
						{    //main mode wird evenetuell noch korrigieren mit schieben
							m_Dummy_special_defend = false;
							m_Dummy_special_defend_attack = false;
						}

						//Der bot sollte möglichst weit nach rechts gehen aber natürlich nicht ins freeze

						if (m_Core.m_Pos.x < 427 * 32 + 15)
						{
							m_Input.m_Direction = 1;
						}
						else
						{
							m_Input.m_Direction = -1;
						}

					}

				}
				else //wenn kein gegner mehr im Ruler bereich is
				{
					m_Dummy_special_defend = false;
					m_Dummy_special_defend_attack = false;
				}
			}
			else if (m_Dummy_mode18 == 2) //different wayblock mode
			{
				//rest on tick
				m_Input.m_Hook = 0;
				m_Input.m_Jump = 0;
				m_Input.m_Direction = 0;
				m_LatestInput.m_Fire = 0;
				m_Input.m_Fire = 0;
				if (Server()->Tick() % 30 == 0)
				{
					SetWeapon(0);
				}
				//if (Server()->Tick() % 5 == 0)
				//{
				//	GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);
				//}

				//Selfkills (bit random but they work)
				if (isFreezed)
				{
					//wenn der bot freeze is warte erstmal n paar sekunden und dann kill dich
					if (Server()->Tick() % 300 == 0)
					{
						Die(m_pPlayer->GetCID(), WEAPON_SELF);
						m_Dummy_happy = false;
					}
				}



				CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler2(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					//Check ob an notstand mode18 = 0 übergeben
					if (pChr->m_FreezeTime == 0)
					{
						m_Dummy_bored = false;
						m_Dummy_bored_counter = 0;
						m_Dummy_mode18 = 0;
					}




					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

					m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

					m_Input.m_Jump = 1;

					if (pChr->m_Pos.y > m_Core.m_Pos.y && pChr->m_Pos.x > m_Core.m_Pos.x + 20) //solange der bot über dem gegner ist (damit er wenn er ihn weg hammert nicht weiter hookt)
					{
						m_Input.m_Hook = 1;
					}

					if (m_Core.m_Pos.x > 420 * 32)
					{
						m_Input.m_Direction = -1;
					}

					if (pChr->m_Pos.y < m_Core.m_Pos.y + 15)
					{
						m_LatestInput.m_Fire++;
						m_Input.m_Fire++;
					}

				}
				else //lieblings position finden wenn nichts abgeht
				{
					//               old: 421 * 32
					if (m_Core.m_Pos.x < 423 * 32)
					{
						m_Input.m_Direction = 1;
					}
					//                   old: 422 * 32 + 30
					else if (m_Core.m_Pos.x > 424 * 32 + 30)
					{
						m_Input.m_Direction = -1;
					}
				}
			}
			else if (m_Dummy_mode18 == 1) //attack in tunnel
			{
				//Selfkills (bit random but they work)
				if (isFreezed)
				{
					//wenn der bot freeze is warte erstmal n paar sekunden und dann kill dich
					if (Server()->Tick() % 300 == 0)
					{
						Die(m_pPlayer->GetCID(), WEAPON_SELF);
					}
				}

				//stay on position

				if (m_Core.m_Pos.x < 426 * 32 + 10) // zu weit links
				{
					m_Input.m_Direction = 1; //geh rechts
				}
				else if (m_Core.m_Pos.x > 428 * 32 - 10) //zu weit rechts
				{
					m_Input.m_Direction = -1; // geh links
				}
				else if (m_Core.m_Pos.x > 428 * 32 + 10) // viel zu weit rechts
				{
					m_Input.m_Direction = -1; // geh links
					m_Input.m_Jump = 1;
				}
				else
				{
					CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRulerWB(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{
						if (pChr->m_Pos.x < 436 * 32) //wenn er ganz weit über dem freeze auf der kante ist (hooke direkt)
						{
							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
						}
						else //wenn der Gegner weiter hinter dem unhook ist (hook über den Gegner um ihn trozdem zu treffen und das unhook zu umgehen)
						{
							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x - 50;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x - 50;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
						}


						//char aBuf[256];
						//str_format(aBuf, sizeof(aBuf), "targX: %d = %d - %d", m_Input.m_TargetX, pChr->m_Pos.x, m_Pos.x);
						//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);


						//m_Input.m_Hook = 0;
						CCharacter *pChr = GameServer()->m_World.ClosestCharTypeTunnel(m_Pos, true);
						if (pChr && pChr->IsAlive())
						{
							//wenn jemand im tunnel is check ob du nicht ausversehen den hookst anstatt des ziels in der WB area
							if (pChr->m_Pos.x < m_Core.m_Pos.x) //hooke nur wenn kein Gegner rechts von dem bot im tunnel is (da er sonst ziemlich wahrscheinlich den hooken würde)
							{
								m_Input.m_Hook = 1;
							}

						}
						else
						{
							//wenn eh keiner im tunnel is hau raus dat ding
							m_Input.m_Hook = 1;
						}

						//schau ob sich der gegner bewegt und der bot grad nicht mehr am angreifen iss dann resette falls er davor halt misshookt hat
						//geht nich -.-
						if (m_Core.m_HookState != HOOK_FLYING && m_Core.m_HookState != HOOK_GRABBED)
						{
							if (Server()->Tick() % 10 == 0)
							{
								m_Input.m_Hook = 0;
							}
						}




						if (m_Core.m_Vel.x > 3.0f)
						{
							m_Input.m_Direction = -1;
						}
						else
						{
							m_Input.m_Direction = 0;
						}

					}
					else
					{
						m_Dummy_mode18 = 0;
					}
				}



			}
			else if (m_Dummy_mode18 == 0) //main mode
			{
				//if (mode18_main_init)
				//{
				//	//initialzing main mode...
				//	//resetting stuff...
				//	m_Input.m_Hook = 0;
				//}

				//m_Input.m_Hook = 0;
				//if (m_Core.m_HookState == HOOK_FLYING)
				//	m_Input.m_Hook = 1;
				//else if (m_Core.m_HookState == HOOK_GRABBED)
				//	m_Input.m_Hook = 1;
				//else
				//	m_Input.m_Hook = 0;

				m_Input.m_Jump = 0;
				m_Input.m_Direction = 0;
				m_LatestInput.m_Fire = 0;
				m_Input.m_Fire = 0;





				//char aBuf[256];
				//str_format(aBuf, sizeof(aBuf), "speed:  x: %f y: %f speed pChr:  x: %f y: %f", m_Core.m_Vel.x, m_Core.m_Vel.y);

				//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);


				if (1 == 2)
				{
					CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{
						char aBuf[256];
						str_format(aBuf, sizeof(aBuf), "speed pChr:  x: %f y: %f", pChr->m_Core.m_Vel.x, pChr->m_Core.m_Vel.y);

						//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);
					}
				}



				//m_pPlayer->m_TeeInfos.m_Name = aBuf; 

				if (m_Core.m_Vel.x > 1.0f)
				{
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "speed: schneller als 1");
				}


				//Check ob jemand in der linken freeze wand is

				CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRulerLeftFreeze(m_Pos, true);  //wenn jemand rechts im freeze liegt
				if (pChr && pChr->IsAlive()) // wenn ein spieler rechts im freeze lebt
				{  //----> versuche im notstand nicht den gegner auch da rein zu hauen da ist ja jetzt voll

					m_Dummy_left_freeze_full = true;
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Da liegt einer im freeze");
				}
				else // wenn da keiner is fülle diesen spot (linke freeze wand im ruler spot)
				{
					m_Dummy_left_freeze_full = false;
				}





				//hardcodet selfkill
				if (m_Core.m_Pos.x < 390 * 32)  //Links am spawn runter
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Links am spawn runter");
				}
				else if (m_Core.m_Pos.y < 204 * 32 && m_Core.m_Pos.x < 415 * 32) //freeze decke am spawn
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze decke am spawn");
				}
				else if (m_Core.m_Pos.y > 218 * 32 + 31 /* für tee balance*/ && m_Core.m_Pos.x < 415 * 32) //freeze boden am spawn
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze boden am spawn");
				}
				else if (m_Core.m_Pos.y < 215 * 32 && m_Core.m_Pos.y > 213 * 32 && m_Core.m_Pos.x > 415 * 32 && m_Core.m_Pos.x < 428 * 32) //freeze decke im tunnel
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze decke im tunnel");
				}
				else if (m_Core.m_Pos.y > 222 * 32) //freeze becken unter area
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze becken unter area");
				}
				else if (m_Core.m_Pos.y > 213 * 32 && m_Core.m_Pos.x > 436 * 32) //freeze rechts neben freeze becken
				{
					//Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze rechts neben freeze becken");
				}
				else if (m_Core.m_Pos.x > 469 * 32) //zu weit ganz rechts in der ruler area
				{
					//Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "zu weit ganz rechts in der ruler area");
				}
				else if (m_Core.m_Pos.y > 211 * 32 + 34 && m_Core.m_Pos.x > 455 * 32) //alles freeze am boden rechts in der area
				{
					//Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "freeze boden rechts der area");
				}


				// Movement
				/*
				NEW MOVEMENT TO BLOCK AREA STRUCTURE :)

				After spawning the bot thinks about what way he shoudl choose.
				After he found one he stopps thinking until he respawns agian.

				if he thinks the tunnel is shit he goes trough the window
				
				*/

				if (!m_Dummy_planned_movment)
				{
					CCharacter *pChr = GameServer()->m_World.ClosestCharTypeTunnel(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{
						if (pChr->m_Core.m_Vel.x < 3.3f) //found a slow bob in tunnel
						{
							m_Dummy_movement_to_block_area_style_window = true;
						}
					}

					m_Dummy_planned_movment = true;
				}



				if (m_Dummy_movement_to_block_area_style_window)
				{
					if (m_Core.m_Pos.x < 415 * 32)
					{
						m_Input.m_Direction = 1;

						if (m_Core.m_Pos.x > 404 * 32 && IsGrounded())
						{
							m_Input.m_Jump = 1;
						}
						if (m_Core.m_Pos.y < 208 * 32)
						{
							m_Input.m_Jump = 1;
						}

						if (m_Core.m_Pos.x > 410 * 32)
						{
							m_Input.m_TargetX = 200;
							m_Input.m_TargetY = 70;
							if (m_Core.m_Pos.x > 413 * 32)
							{
								m_Input.m_Hook = 1;
							}
						}
					}
					else //not needed but safty xD when the bot managed it to get into the ruler area change to old movement
					{
						m_Dummy_movement_to_block_area_style_window = false;
					}


					//something went wrong:
					if (m_Core.m_Pos.y > 214 * 32)
					{
						m_Input.m_Jump = 1;
						m_Dummy_movement_to_block_area_style_window = false;
					}

				}
				else //down way
				{

					//CheckFatsOnSpawn

					if (m_Core.m_Pos.x < 406 * 32)
					{
						CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
						if (pChr && pChr->IsAlive())
						{

							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;


							if (pChr->m_Pos.x < 407 * 32 && pChr->m_Pos.y > 212 * 32 && pChr->m_Pos.y < 215 * 32 && pChr->m_Pos.x > m_Core.m_Pos.x) //wenn ein im weg stehender tee auf der spawn plattform gefunden wurde
							{
								SetWeapon(0); //hol den hammer raus!
								if (pChr->m_Pos.x - m_Core.m_Pos.x < 30) //wenn der typ nahe bei dem bot ist
								{
									if (m_FreezeTick == 0) //nicht rum schrein
									{
										m_LatestInput.m_Fire++;
										m_Input.m_Fire++;
									}


									if (Server()->Tick() % 10 == 0)
									{
										GameServer()->SendEmoticon(m_pPlayer->GetCID(), 9); //angry
									}
								}
							}
							else
							{
								if (Server()->Tick() % 20 == 0)
								{
									SetWeapon(1); //pack den hammer weg
								}
							}
						}
					}


					//Check attacked on spawn
					if (m_Core.m_Pos.x < 412 * 32 && m_Core.m_Pos.y > 217 * 32 && m_Core.m_Vel.x < -0.5f)
					{
						m_Input.m_Jump = 1;
						m_Dummy_AttackedOnSpawn = true;
					}
					if (IsGrounded())
					{
						m_Dummy_AttackedOnSpawn = false;
					}
					if (m_Dummy_AttackedOnSpawn)
					{
						if (Server()->Tick() % 100 == 0) //this shitty stuff can set it right after activation to false but i dont care
						{
							m_Dummy_AttackedOnSpawn = false;
						}
					}


					if (m_Dummy_AttackedOnSpawn)
					{
						int r = rand() % 88; // #noRACISMIM   hitler was fggt    but just because he claimed this number i wont stop using it fuck him and his claims i dont care about him i use this number as my number. it is a statement agianst his usage! we have to fight!

						if (r > 44)
						{
							m_Input.m_Fire++;
						}

						int duNIPPEL = rand() % 1337;
						if (duNIPPEL > 420)
						{
							SetWeapon(0);
						}

						CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
						if (pChr && pChr->IsAlive())
						{
							int r = rand() % 10 - 10;

							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y - r;

							if (Server()->Tick() % 13 == 0)
							{
								GameServer()->SendEmoticon(m_pPlayer->GetCID(), 9);
							}

							if (m_Core.m_HookState == HOOK_GRABBED || m_Core.m_Pos.y < 216 * 32 && pChr->m_Pos.x > 404 * 32 || pChr->m_Pos.x > 405 * 32 && m_Core.m_Pos.x > 404 * 32 + 20)
							{
								m_Input.m_Hook = 1;
								if (Server()->Tick() % 10 == 0)
								{
									int x = rand() % 20;
									int y = rand() % 20 - 10;
									m_Input.m_TargetX = x;
									m_Input.m_TargetY = y;
								}
							}

						}
					}



					//CheckSlowDudesInTunnel

					if (m_Core.m_Pos.x > 415 * 32 && m_Core.m_Pos.y > 214 * 32) //wenn bot im tunnel ist
					{
						CCharacter *pChr = GameServer()->m_World.ClosestCharTypeTunnel(m_Pos, true);
						if (pChr && pChr->IsAlive())
						{
							if (pChr->m_Core.m_Vel.x < 7.8f) //wenn der nächste spieler im tunnel ein slowdude is 
							{
								//HauDenBau
								SetWeapon(0); //hol den hammer raus!

								m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
								m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;

								m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
								m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

								if (m_FreezeTick == 0) //nicht rum schrein
								{
									m_LatestInput.m_Fire++;
									m_Input.m_Fire++;
								}

								if (Server()->Tick() % 10 == 0)  //angry emotes machen
								{
									GameServer()->SendEmoticon(m_pPlayer->GetCID(), 9);
								}


							}
						}
					}


					//CheckSpeedInTunnel
					if (m_Core.m_Pos.x > 425 * 32 && m_Core.m_Pos.y > 214 * 32 && m_Core.m_Vel.x < 9.4f) //wenn nich genung speed zum wb spot springen
					{
						m_Dummy_get_speed = true;
					}


					if (m_Dummy_get_speed) //wenn schwung holen == true (tunnel)
					{
						if (m_Core.m_Pos.x > 422 * 32) //zu weit rechts
						{
							//---> hol schwung für den jump
							m_Input.m_Direction = -1;

							//new hammer agressive in the walkdirection to free the way
							if (m_FreezeTime == 0)
							{
								m_Input.m_TargetX = -200;
								m_Input.m_TargetY = -2;
								if (Server()->Tick() % 20 == 0)
								{
									SetWeapon(0);
								}
								if (Server()->Tick() % 25 == 0)
								{
									m_Input.m_Fire++;
									m_LatestInput.m_Fire++;
								}
							}
						}
						else //wenn weit genung links
						{
							//dann kann das normale movement von dort aus genung schwung auf bauen
							m_Dummy_get_speed = false;
						}
					}
					else
					{
						if (m_Core.m_Pos.x < 415 * 32) //bis zum tunnel laufen
						{
							m_Input.m_Direction = 1;

						}
						else if (m_Core.m_Pos.x < 440 * 32 && m_Core.m_Pos.y > 213 * 32) //im tunnel laufen
						{
							m_Input.m_Direction = 1;

						}


						//externe if abfrage weil laufen während sprinegn xD

						if (m_Core.m_Pos.x > 413 * 32 && m_Core.m_Pos.x < 415 * 32) // in den tunnel springen
						{
							m_Input.m_Jump = 1;
							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "triggerd");
							//m_Input.m_Jump = 0;
						}
						else if (m_Core.m_Pos.x > 428 * 32 - 20 && m_Core.m_Pos.y > 213 * 32) // im tunnel springen
						{
							m_Input.m_Jump = 1;
						}



						// externen springen aufhören für dj

						if (m_Core.m_Pos.x > 428 * 32 && m_Core.m_Pos.y > 213 * 32) // im tunnel springen nicht mehr springen
						{
							m_Input.m_Jump = 0;
							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "triggerd");
						}


						//nochmal extern weil springen während springen

						if (m_Core.m_Pos.x > 430 * 32 && m_Core.m_Pos.y > 213 * 32) // im tunnel springen springen
						{
							m_Input.m_Jump = 1;
							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "triggerd");
						}



						if (m_Core.m_Pos.x > 431 * 32 && m_Core.m_Pos.y > 213 * 32) //jump refillen für wayblock spot
						{
							m_Input.m_Jump = 0;
						}
					}
				}


				// *****************************************************
				// Way Block spot
				// *****************************************************
				// wayblockspot < 213 [y]


				//externer wayblockspot stuff

				//Checken ob der bot in seinem arial angegriffen wird obwohl kein nostand links ausgerufen wurde



				//wird nicht genutzt weil das preventive springen vom boden aus schluss endlich schlimmer ausgeht als der dj
				/*
				if (m_Core.m_Pos.y < 213 * 32 && m_Core.m_Pos.x > (427 * 32) - 20 && m_Core.m_Pos.x < (428 * 32) + 10) //wenn der bot sich an seinem ruler spot befindet
				{
				//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich mag diesen ort :)");

				if (!m_Dummy_wb_hooked && !m_Dummy_emergency && !m_Dummy_pushing && m_Core.m_Vel.x > 0.90f) //wenn der bot sich auf das freeze zubewegt obwohl er nicht selber läuft
				{
				// --> er wird wahrscheinlich gehookt oder anderweitig extern angegriffen
				// --> schutzmaßnahmen treffen

				GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "AAAh ich werde angegriffen");
				m_Input.m_Jump = 1;
				}
				m_Dummy_pushing = false;
				m_Dummy_emergency = false;
				m_Dummy_wb_hooked = false;
				}
				*/

				//moved dynamic selfkills outside internal wb spot
				//self kill im freeze
				//New Testy selfkill kill if isFreezed and vel 0
				if (!isFreezed || m_Core.m_Vel.x < -0.5f || m_Core.m_Vel.x > 0.5f || m_Core.m_Vel.y != 0.000000f)
				{
					//mach nichts lol brauche nur das else is einfacher
				}
				else
				{
					if (Server()->Tick() % 150 == 0)
						Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}



				//Bools zurueck setzten
				m_Dummy_pushing = false;
				m_Dummy_emergency = false;
				m_Dummy_wb_hooked = false;
				m_Dummy_happy = false;

				//normaler internen wb spot stuff

				//if (m_Core.m_Pos.y < 213 * 32) //old new added a x check idk why the was no
				if (m_Core.m_Pos.y < 213 * 32 && m_Core.m_Pos.x > 415 * 32)
				{


					//Old self kill kill if freeze
					//if (m_Core.m_Pos.y < 201 * 32) // decke
					//{
					//	Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//	//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "suicide reason: roof rulerspot");
					//}
					//else if (m_Core.m_Pos.x < 417 * 32 && m_Core.m_Pos.x > 414 * 32 + 17 && isFreezed) //linker streifen xD
					//{
					//	Die(m_pPlayer->GetCID(), WEAPON_SELF);
					//	//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "suicide reason: left wall rulerspot");
					//}



					//New stuff RANDOM STOFF ROFL
					//if the bot is in his wb position an bored and there is no actual danger 
					// ---> flick some aim and fire around xD

					//m_Dummy_bored_cuz_nothing_happens = true;

					//dont activate all the time and dunno how to make a cool activator code so fuck it rofl


					if (m_Dummy_bored_cuz_nothing_happens)
					{
						CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
						if (pChr && pChr->IsAlive() && m_FreezeTime == 0)
						{
							if (pChr->m_Pos.x < 429 * 32 && pChr->m_Core.m_Vel.x < 4.3f)
							{
								int x = rand() % 100 - 50;
								int y = rand() % 100;

								m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x + x;
								m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y + y;


								//doesnt work. i dont care. i dont fix. i just comment it out cuz fuck life is a bitch


								//int fr = rand() % 2000;
								//if (fr < 1300)
								//{
								//	m_Dummy_bored_shootin = true;
								//}

								//if (m_Dummy_bored_shootin)
								//{
								//	m_Input.m_Fire++;
								//	m_LatestInput.m_Fire++;

								//	if (Server()->Tick() % 50 == 0)
								//	{
								//		m_Dummy_bored_shootin = false;
								//	}
								//}

							}
						}
					}




					//TODO(1): keep this structur in mind this makes not much sence
					// the bool m_Dummy_happy is just true if a enemy is in the ruler area because all code below depends on a enemy in ruler area
					// maybe rework this shit



					//                                                      
					//                                               --->   Ruler   <---    testy own class just search in ruler area

					CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler(m_Pos, true);  //position anderer spieler mit pikus aimbot abfragen
					if (pChr && pChr->IsAlive())
					{
                                 
						if (pChr->m_FreezeTime == 0) //if enemy in ruler spot is unfreeze -->notstand panic
						{
							//m_Core.m_ActiveWeapon = WEAPON_HAMMER;
							SetWeapon(0);


							//testy sollte eig auch am anfang des modes passen
							//m_Input.m_Direction = 0;

							//if (m_Core.m_HookState == HOOK_FLYING)
							//	m_Input.m_Hook = 1;
							//else if (m_Core.m_HookState == HOOK_GRABBED)
							//	m_Input.m_Hook = 1;
							//else
							//	m_Input.m_Hook = 0;

							char aBuf[256];
							str_format(aBuf, sizeof(aBuf), "hookstate: %x", m_Input.m_Hook);
							//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);

							m_Dummy_emergency = true;




							if (!m_Dummy_left_freeze_full)
							{
								//                                                                                                        x > 5 = 3       <-- ignorieren xD


								//                                                                                                          hier wird das schieben an das andere schieben 
								//                                                                                                    übergeben weil er hier von weiter weg anfängt zu schieben 
								//                                                                                                und das kürzere schieben macht dann den ganzen stuff das der bot nicht selber rein läuft  
								//                                                                                                ja ich weiss das ist ziemlich umständlich xD
								//                                                                                                      aber das hat schon sinn das hier wird aufgerufen wenn der weit weg is und freezed und
								//                                                                                                  übergibt dann an die abfrage die auch aufgerufen wird wenn jemand unfreeze is jedoch nir auf kurze distanz

								//                                                                                                          tja aber das mit dem übergeben klappt ja nich wirklich


								//                                                                                                           Deswegen hab ich den code ganz gelöscht und nur ein teil als || in die "freeze protection & schieberrei" geklatscht
								//                                                                                                         ----> hier is ein berg an kommentaren zu nicht existentem code lol    gut das nur ich hier rum stöber hueueueu
								//start sequenz
								// Blocke spieler in die linke freeze wand

								if (!m_Dummy_jumped)
								{
									//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "boing!");
									m_Input.m_Jump = 1;
									m_Dummy_jumped = true;
								}
								else
								{
									m_Input.m_Jump = 0;
								}



								if (!m_Dummy_hooked)
								{
									if (Server()->Tick() % 30 == 0)
										m_Dummy_hook_delay = true;

									//testy removed hook here i dont know why but all works pretty good still xD
									if (m_Dummy_hook_delay)
										//m_Input.m_Hook = 1;

										if (Server()->Tick() % 200 == 0)
										{
											m_Dummy_hooked = true;
											m_Input.m_Hook = 0;
										}

								}

								if (!m_Dummy_moved_left)
								{
									if (m_Core.m_Pos.x > 419 * 32 + 20)
										m_Input.m_Direction = -1;
									else
										m_Input.m_Direction = 1;

									if (Server()->Tick() % 200 == 0)
									{
										m_Dummy_moved_left = true;
										m_Input.m_Direction = 0;
									}

								}
							}







							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "NOTSTAND");

							if (Server()->Tick() % 30 == 0)  //angry emotes machen
							{
								GameServer()->SendEmoticon(m_pPlayer->GetCID(), 9);
							}



							CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler(m_Pos, true); //aimbot + hammerspam
							if (pChr && pChr->IsAlive())
							{

								m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
								m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
								m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
								m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;


								//schiess delay
								if (Server()->Tick() >= m_EmoteTickNext)
								{
									m_pPlayer->m_LastEmote = Server()->Tick();


									//GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);

									if (m_FreezeTick == 0) //nicht rum schrein
									{
										m_LatestInput.m_Fire++;
										m_Input.m_Fire++;
									}

									m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() / 4;
								}
							}







							//Blocke gefreezte gegner für immer 


							//TODO:
							//das is ein linke seite block wenn hier voll is sollte man anders vorgehen
							//                           früher war es y > 210   aber change weil er während er ihn hochzieht dann nicht mehr das hooken aufhört
							if (pChr->m_FreezeTime > 0 && pChr->m_Pos.y > 204 * 32 && pChr->m_Pos.x > 422 * 32) //wenn ein gegner weit genung rechts freeze am boden liegt
							{
								// soll der bot sich einer position links des spielers nähern
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "hab n opfer gefunden");

								if (m_Core.m_Pos.x + (5 * 32 + 40) < pChr->m_Pos.x) // er versucht 5 tiles links des gefreezten gegner zu kommen
								{
									m_Input.m_Direction = -1;

									if (m_Core.m_Pos.x > pChr->m_Pos.x && m_Core.m_Pos.x < pChr->m_Pos.x + (4 * 32)) // wenn er 4 tiles rechts des gefreezten gegners is
									{
										m_Input.m_Jump = 1;
										//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "boing!");
									}
								}
								else //wenn der bot links des gefreezten spielers is
								{
									m_Input.m_Jump = 1;
									//echo jump
									//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "boing!");

									m_Input.m_Direction = -1;

									if (m_Core.m_Pos.x < pChr->m_Pos.x) //solange der bot weiter links is
									{
										m_Input.m_Hook = 1;
									}
									else
									{
										m_Input.m_Hook = 0;
									}
								}
							}






							//freeze protection & schieberrei
							//                                                                                                                                                                                                      old (417 * 32 - 60)
							if (pChr->m_Pos.x + 10 < m_Core.m_Pos.x && pChr->m_Pos.y > 211 * 32 && pChr->m_Pos.x < 418 * 32 || pChr->m_FreezeTime > 0 && pChr->m_Pos.y > 210 * 32 && pChr->m_Pos.x < m_Core.m_Pos.x && pChr->m_Pos.x > 417 * 32 - 60) // wenn der spieler neben der linken wand linken freeze wand liegt schiebt ihn der bot rein
							{                                                                                            // oder wenn der spieler weiter weg liegt aber freeze is


								if (!m_Dummy_left_freeze_full) //wenn da niemand is schieb den rein
								{
									// HIER TESTY TESTY CHANGES  211 * 32 + 40 stand hier
									if (pChr->m_Pos.y > 211 * 32 + 40) // wenn der gegner wirklich ganz tief genung is
									{ //                          417 * 32 - 40
										if (m_Core.m_Pos.x > 418 * 32) // aber nicht selber ins freeze laufen
										{
											m_Input.m_Direction = -1;




											//Check ob der gegener freeze is

											if (pChr->m_FreezeTime > 0)
											{
												m_LatestInput.m_Fire = 0; //nicht schiessen ofc xD (doch is schon besser xD)
												m_Input.m_Fire = 0;

												//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "haha owned");
											}

											//letzten stupser geben (sonst gibs bugs kb zu fixen)
											if (pChr->isFreezed) //wenn er schon im freeze is
											{
												m_LatestInput.m_Fire = 1; //hau ihn an die wand
												m_Input.m_Fire = 1;
											}

										}
										else
										{
											m_Input.m_Direction = 1;
											//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "stop error code: 1");
											if (pChr->m_FreezeTime > 0)
											{
												m_LatestInput.m_Fire = 0; //nicht schiessen ofc xD (doch is schon besser xD)
												m_Input.m_Fire = 0;

												//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "haha owned");
											}
											//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "ich halte das auf.");
											//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich will da nich rein laufen");
										}



									}
									else //wenn der gegner nicht tief genung ist
									{

										m_Input.m_Direction = 1;

										if (pChr->m_FreezeTime > 0)
										{
											m_LatestInput.m_Fire = 0; //nicht schiessen ofc xD (doch is schon besser xD)
											m_Input.m_Fire = 0;

											//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "haha owned");
										}
									}



								}
								else //wenn da schon jemand liegt 
								{
									// sag das mal xD
									//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "da liegt schon einer");
								}
							}
							else if (m_Core.m_Pos.x < 419 * 32 + 10) //sonst mehr abstand halten
							{
								m_Input.m_Direction = 1;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "stop error code: 2");
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich will da nich rein laufen");
							}
							// else // wenn nichts los is erstmal stehen bleiben 






							//freeze protection decke mit double jump wenn hammer

							if (m_Core.m_Vel.y < 20.0f && m_Core.m_Pos.y < 207 * 32)  // wenn der tee nach oben gehammert wird
							{
								if (m_Core.m_Pos.y > 206 * 32) //ab 206 würd er so oder so ins freeze springen
									m_Input.m_Jump = 1;

								if (m_Core.m_Pos.y < pChr->m_Pos.y) //wenn der bot über dem spieler is soll er hooken
									m_Input.m_Hook = 1;
								else
									m_Input.m_Hook = 0;
							}


							//wenn der tee hcoh geschleudert wird
							//                 old 4 (macht aber im postiven bereich kein sinn aber hat geklappt)
							//                 HALLO HIER IST DEIN ICH AUS DER ZUKUNFT: du dummes kind wenn er in der luft hammert dann fliegt er doch nicht nach oben und gerade da musst du es ja perfekt haben ... low
							//if (m_Core.m_Vel.y < 4.0f && m_Core.m_Pos.y < pChr->m_Pos.y) //wenn er schneller als 4 nach oben fliegt und höher als der Gegener ist
							// lass das mit speed weg und mach lieber was mit höhe
							if (m_Core.m_Pos.y < 207 * 32 && m_Core.m_Pos.y < pChr->m_Pos.y)
							{
								//in hammer position bewegen
								if (m_Core.m_Pos.x > 418 * 32 + 20) //nicht ins freeze laufen
								{
									if (m_Core.m_Pos.x > pChr->m_Pos.x - 45) //zu weit rechts von hammer position
									{
										m_Input.m_Direction = -1; //gehe links
																  //GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich will da nich rein laufen");
									}
									else if (m_Core.m_Pos.x < pChr->m_Pos.x - 39) // zu weit links von hammer position
									{
										m_Input.m_Direction = 1;
										//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "stop error code: 3");
									}
									else  //im hammer bereich
									{
										m_Input.m_Direction = 0; //bleib da
									}
								}
							}


							//Check ob der gegener freeze is

							if (pChr->m_FreezeTime > 0 && pChr->m_Pos.y > 208 * 32 && !pChr->isFreezed) //wenn der Gegner tief und freeze is macht es wenig sinn den frei zu hammern
							{
								m_LatestInput.m_Fire = 0; //nicht schiessen 
								m_Input.m_Fire = 0;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "haha owned");
							}



							//Hau den weg (wie dummymode 21)
							if (pChr->m_Pos.x > 418 * 32 && pChr->m_Pos.y > 209 * 32)  //das ganze findet nur im bereich statt wo sonst eh nichts passiert
							{
								//wenn der bot den gegner nicht boosten würde hammer den auch nich weg
								m_LatestInput.m_Fire = 0;
								m_Input.m_Fire = 0;

								if (pChr->m_Core.m_Vel.y < -0.5f && m_Core.m_Pos.y + 15 > pChr->m_Pos.y) //wenn der dude speed nach oben hat
								{
									m_Input.m_Jump = 1;
									if (m_FreezeTime == 0)
									{
										m_LatestInput.m_Fire++;
										m_Input.m_Fire++;
									}
								}
							}


							//TODO: FIX:
							//der bot unfreezed den gegner ab einer gewissen höhe wenn er rein gehammert wird schau das da was passiert





							//wenn ein tee freeze links neben dem bot liegt werf den einfach wieder ins freeze becken
							//das is bisher ja noch die einzige sicherheits lücke beim wayblocken
							//wenn man ein tee über den bot hammert

							if (pChr->m_Pos.x > 421 * 32 && pChr->m_FreezeTick > 0 && pChr->m_Pos.x < m_Core.m_Pos.x)
							{
								m_Input.m_Jump = 1;
								m_Input.m_Hook = 1;
							}

							//##############################
							// doggeystyle dogeing the freeze
							//##############################

							//during the fight dodge the freezefloor on the left with brain
							if (m_Core.m_Pos.x > 428 * 32 + 20 && m_Core.m_Pos.x < 438 * 32 - 20)
							{
								//very nobrain directions decision
								if (m_Core.m_Pos.x < 432 * 32) //left --> go left
								{
									m_Input.m_Direction = -1;
								}
								else                           //right --> go right
								{
									m_Input.m_Direction = 1;
								}

								//high speed left goto speed
								if (m_Core.m_Vel.x < -6.4f && m_Core.m_Pos.x < 434 * 32)
								{
									m_Input.m_Direction = -1;
								}

								//low speed to the right
								if (m_Core.m_Pos.x > 431 * 32 + 20 && m_Core.m_Vel.x > 3.3f)
								{
									m_Input.m_Direction = 1;
								}
							}


							//m_pPlayer->m_TeeInfos.m_ColorBody = (0 * 255 / 360);
							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Enemy in ruler spot found!");
						}
						else //sonst normal wayblocken und 427 aufsuchen
						{
							//m_Core.m_ActiveWeapon = WEAPON_GUN;
							SetWeapon(1);
							m_Input.m_Jump = 0;

							if (m_Core.m_HookState == HOOK_FLYING)
								m_Input.m_Hook = 1;
							else if (m_Core.m_HookState == HOOK_GRABBED)
								m_Input.m_Hook = 1;
							else
								m_Input.m_Hook = 0;

							//m_pPlayer->m_TeeInfos.m_ColorBody = (120 * 255 / 360);
							//positions check and correction 427


							m_Dummy_jumped = false;
							m_Dummy_hooked = false;
							m_Dummy_moved_left = false;



							if (m_Core.m_Pos.x > 428 * 32 + 15 && m_Dummy_ruled) //wenn viel zu weit ausserhalb der ruler area wo der bot nur hingehookt werden kann
							{
								m_Input.m_Jump = 1;
								m_Input.m_Hook = 1;
							}

							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Prüfe ob zu weit rechts");
							if (m_Core.m_Pos.x < (418 * 32) - 10) // zu weit links -> geh rechts
							{
								m_Input.m_Direction = 1;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "stop error code: 4");
							}
							else if (m_Core.m_Pos.x >(428 * 32) + 10) // zu weit rechts -> geh links
							{
								m_Input.m_Direction = -1;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich bin zuweit rechts...");
							}
							else // im toleranz bereich -> stehen bleiben
							{
								m_Dummy_happy = true;
								m_Dummy_ruled = true;
								m_Input.m_Direction = 0;
								//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "toleranz bereich");
								//m_Input.m_LatestTargetX = 0;
								//m_Input.m_LatestTargetY = 0;


								//stuff im toleranz bereich doon





								// normal wayblock
								CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler(m_Pos, true);  //position anderer spieler mit pikus aimbot abfragen
								if (pChr && pChr->IsAlive())
								{
				

									//m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
									//m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;



									//m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
									//m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

									//m_Input.m_TargetX = 1;//pChr->m_Pos.x - m_Pos.x; //1
									//m_Input.m_TargetY = 0;//pChr->m_Pos.y - m_Pos.y; //0

									//m_LatestInput.m_TargetX = 1;//pChr->m_Pos.x - m_Pos.x;
									//m_LatestInput.m_TargetY = 0;//pChr->m_Pos.y - m_Pos.y;

									//i dunno why there is a if statement under this code and i dont wanna use it 
									//so i made Trick[4] external (woo spagethii code)
									//Trick[4] clears the left freeze
									if (pChr->m_Pos.x < 418 * 32 - 10 && pChr->m_Pos.y > 210 * 32 && pChr->m_Pos.y < 213 * 32 && pChr->isFreezed && pChr->m_Core.m_Vel.y == 0.00f)
									{
										m_DummyFreezeBlockTrick = 4;
									}


									//                                                                                            old was: 418 * 32 + 20          and i have no fkin idea why so i changed to 17
									if (pChr->m_Pos.y < 213 * 32 + 10 && pChr->m_Pos.x < 430 * 32 && pChr->m_Pos.y > 210 * 32 && pChr->m_Pos.x > 417 * 32) // wenn ein spieler auf der linken seite in der ruler area is 
									{
										//wenn ein gegner rechts des bots is prepare für trick[1]
										if (m_Core.m_Pos.x < pChr->m_Pos.x && pChr->m_Pos.x < 429 * 32 + 6)
										{
											m_Input.m_Direction = -1;
											m_Input.m_Jump = 0;

											if (m_Core.m_Pos.x < 422 * 32)
											{
												m_Input.m_Jump = 1;
												m_DummyFreezeBlockTrick = 1;
											}
										}
										//wenn ein gegner links des bots is prepare für tick[3]
										if (m_Core.m_Pos.x > pChr->m_Pos.x && pChr->m_Pos.x < 429 * 32)
										{
											m_Input.m_Direction = 1;
											m_Input.m_Jump = 0;

											if (m_Core.m_Pos.x > 427 * 32 || m_Core.m_Pos.x > pChr->m_Pos.x + (5 * 32))
											{
												m_Input.m_Jump = 1;
												m_DummyFreezeBlockTrick = 3;
											}
										}


									}
									else // wenn spieler irgendwo anders is
									{
										//wenn ein spieler rechts des freezes is und freeze is Tric[2]
										if (pChr->m_Pos.x > 433 * 32 && pChr->m_FreezeTime > 0 && IsGrounded())
										{
											m_DummyFreezeBlockTrick = 2;
										}
									}

								}
							}
						}
					}
					else // wenn kein lebender spieler im ruler spot ist
					{

						//Suche trozdem 427 auf

						if (m_Core.m_Pos.x < (427 * 32) - 20) // zu weit links -> geh rechts
						{
							m_Input.m_Direction = 1;
							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "stop error code: special");
						}
						else if (m_Core.m_Pos.x >(427 * 32) + 40) // zu weit rechts -> geh links
						{
							m_Input.m_Direction = -1;
							//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "Ich bin zuweit rechts...");
						}
					}






					// über das freeze springen wenn rechts der bevorzugenten camp stelle

					if (m_Core.m_Pos.x > 434 * 32)
					{
						m_Input.m_Jump = 1;
					}
					else if (m_Core.m_Pos.x > (434 * 32) - 20 && m_Core.m_Pos.x < (434 * 32) + 20) // bei flug über freeze jump wd holen
					{
						m_Input.m_Jump = 0;
						//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "refilling jump");
					}

					//new testy moved tricks into Wayblocker area (y < 213 && x > 215) (was external)
					//TRICKS
					if (1 == 1)
					{
						CCharacter *pChr = GameServer()->m_World.ClosestCharTypeRuler(m_Pos, true);
						if (pChr && pChr->IsAlive())
						{
							if (!m_Dummy_emergency && m_Core.m_Pos.x > 415 && m_Core.m_Pos.y < 213 * 32 && m_DummyFreezeBlockTrick != 0) //as long as no enemy is unfreeze in base --->  do some trickzz
							{
								//Trick reset all  
								//resett in the tricks because trick1 doesnt want it
								//m_Input.m_Hook = 0;
								//m_Input.m_Jump = 0;
								//m_Input.m_Direction = 0;
								//m_LatestInput.m_Fire = 0;
								//m_Input.m_Fire = 0;

								//off tricks when not gud to make tricks#
								if (pChr->m_FreezeTime == 0)
								{
									m_DummyFreezeBlockTrick = 0;
									m_Dummy_trick_panic_check_delay = 0;
									m_Dummy_trick3_panic_check = false;
									m_Dummy_trick3_start_count = false;
									m_Dummy_trick3_panic = false;
									m_Dummy_trick4_hasstartpos = false;
								}


								if (m_DummyFreezeBlockTrick == 1) //Tick[1] enemy on the right
								{
									if (pChr->isFreezed)
									{
										m_DummyFreezeBlockTrick = 0; //stop trick if enemy is in freeze
									}
									m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
									m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
									m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
									m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

									if (Server()->Tick() % 40 == 0)
									{
										SetWeapon(0);
									}


									if (pChr->m_Pos.x < m_Core.m_Pos.x && pChr->m_Pos.x > m_Core.m_Pos.x - 180) //if enemy is on the left in hammer distance
									{
										m_Input.m_Fire++;
										m_LatestInput.m_Fire++;
									}

									if (m_Core.m_Pos.y < 210 * 32 + 10)
									{
										m_Dummy_start_hook = true;
									}

									if (m_Dummy_start_hook)
									{
										if (Server()->Tick() % 80 == 0 || pChr->m_Pos.x < m_Core.m_Pos.x + 22)
										{
											m_Dummy_start_hook = false;
										}
									}


									if (m_Dummy_start_hook)
									{
										m_Input.m_Hook = 1;
									}
									else
									{
										m_Input.m_Hook = 0;
									}
								}
								else if (m_DummyFreezeBlockTrick == 2) //enemy on the right plattform --> swing him away
								{
									m_Input.m_Hook = 0;
									m_Input.m_Jump = 0;
									m_Input.m_Direction = 0;
									m_LatestInput.m_Fire = 0;
									m_Input.m_Fire = 0;

									if (Server()->Tick() % 50 == 0)
									{
										m_Dummy_bored_counter++;
										GameServer()->SendEmoticon(m_pPlayer->GetCID(), 7);
									}

									if (m_Core.m_Pos.x < 438 * 32) //first go right
									{
										m_Input.m_Direction = 1;
									}

									if (m_Core.m_Pos.x > 428 * 32 && m_Core.m_Pos.x < 430 * 32) //first jump
									{
										m_Input.m_Jump = 1;
									}

									if (m_Core.m_Pos.x > 427 * 32) //aim and swing
									{
										m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
										m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
										m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
										m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;


										if (m_Core.m_Pos.x > 427 * 32 + 30 && pChr->m_Pos.y < 214 * 32)
										{
											m_Input.m_Hook = 1;
											if (Server()->Tick() % 10 == 0)
											{
												int x = rand() % 100 - 50;
												int y = rand() % 100 - 50;

												m_Input.m_TargetX = x;
												m_Input.m_TargetY = y;
											}
											//random shooting xD
											int r = rand() % 200 + 10;
											if (Server()->Tick() % r == 0 && m_FreezeTime == 0)
											{
												m_Input.m_Fire++;
												m_LatestInput.m_Fire++;
											}
										}
									}

									//also this trick needs some freeze dogining because sometime huge speed fucks the bot
									//and NOW THIS CODE is here to fuck the high speed 
									// yo!
									if (m_Core.m_Pos.x > 440 * 32)
									{
										m_Input.m_Direction = -1;
									}
									if (m_Core.m_Pos.x > 439 * 32 + 20 && m_Core.m_Pos.x < 440 * 32)
									{
										m_Input.m_Direction = 0;
									}


								}
								else if (m_DummyFreezeBlockTrick == 3) //enemy on the left swing him to the right
								{
									m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
									m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
									m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
									m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;



									if (m_Core.m_Pos.y < 210 * 32 + 10)
									{
										m_Dummy_start_hook = true;
										m_Dummy_trick3_start_count = true;
									}

									if (m_Dummy_start_hook)
									{
										if (Server()->Tick() % 80 == 0 || pChr->m_Pos.x > m_Core.m_Pos.x - 22)
										{
											m_Dummy_start_hook = false;
										}
									}


									if (m_Dummy_start_hook)
									{
										m_Input.m_Hook = 1;
									}
									else
									{
										m_Input.m_Hook = 0;
									}

									if (m_Core.m_Pos.x < 429 * 32)
									{
										m_Input.m_Direction = 1;
									}
									else
									{
										m_Input.m_Direction = -1;
									}


									//if he lands on the right plattform switch trick xD
									if (pChr->m_Pos.x > 433 * 32 && pChr->m_Core.m_Vel.y == 0.0f)
									{
										m_DummyFreezeBlockTrick = 2;
									}


									//Check for trick went wrong --> trick3 panic activation
									if (m_Dummy_trick3_start_count)
									{
										m_Dummy_trick_panic_check_delay++;
									}
									if (m_Dummy_trick_panic_check_delay > 52)
									{
										m_Dummy_trick3_panic_check = true;
									}
									if (m_Dummy_trick3_panic_check)
									{
										if (pChr->m_Pos.x < 430 * 32 && pChr->m_Pos.x > 426 * 32 + 10 && pChr->IsGrounded())
										{
											m_Dummy_trick3_panic = true;
											m_Dummy_trick3_panic_left = true;
										}
									}
									if (m_Dummy_trick3_panic)
									{
										//stuck --> go left and swing him down
										m_Input.m_Direction = 1;
										if (m_Core.m_Pos.x < 425 * 32)
										{
											m_Dummy_trick3_panic_left = false;
										}

										if (m_Dummy_trick3_panic_left)
										{
											m_Input.m_Direction = -1;
										}
										else
										{
											if (m_Core.m_Pos.y < 212 * 32 + 10)
											{
												m_Input.m_Hook = 1;
											}
										}
									}
								}
								else if (m_DummyFreezeBlockTrick == 4) //clear left freeze
								{
									m_Input.m_Hook = 0;
									m_Input.m_Jump = 0;
									m_Input.m_Direction = 0;
									m_LatestInput.m_Fire = 0;
									m_Input.m_Fire = 0;


									if (!m_Dummy_trick4_hasstartpos)
									{
										if (m_Core.m_Pos.x < 423 * 32 - 10)
										{
											m_Input.m_Direction = 1;
										}
										else if (m_Core.m_Pos.x > 424 * 32 - 20)
										{
											m_Input.m_Direction = -1;
										}
										else
										{
											m_Dummy_trick4_hasstartpos = true;
										}
									}
									else //has start pos
									{
										m_Input.m_TargetX = -200;
										m_Input.m_TargetY = -2;
										if (pChr->isFreezed)
										{
											m_Input.m_Hook = 1;
										}
										else
										{
											m_Input.m_Hook = 0;
											m_DummyFreezeBlockTrick = 0; //fuck it too lazy normal stuff shoudl do the rest xD
										}
										if (Server()->Tick() % 7 == 0)
										{
											m_Input.m_Hook = 0;
										}
									}
								}




							}
						}
						else //nobody alive in ruler area --> stop tricks
						{
							m_Dummy_trick4_hasstartpos = false;
							m_Dummy_trick3_panic = false;
							m_Dummy_trick3_start_count = false;
							m_Dummy_trick3_panic_check = false;
							m_Dummy_trick_panic_check_delay = 0;
							m_DummyFreezeBlockTrick = 0;
						}
					}


				}




				//##################################
				// 29 only protections and doge moves
				//##################################


				//Super last jumpy freeze protection o.O
				//saves alot bot live im very sure
				//#longlivesthebotrofl

				if (m_Core.m_Pos.x > 429 * 32 && m_Core.m_Pos.x < 436 * 32 && m_Core.m_Pos.y < 214 * 32) //dangerous area over the freeze
				{
					//first check! too low?
					if (m_Core.m_Pos.y > 211 * 32 + 10 && IsGrounded() == false)
					{
						m_Input.m_Jump = 1;
						m_Input.m_Hook = 1;
						if (Server()->Tick() % 4 == 0)
						{
							m_Input.m_Jump = 0;
						}
					}

					//second check! too speedy?
					if (m_Core.m_Pos.y > 209 * 32 && m_Core.m_Vel.y > 5.6f)
					{
						m_Input.m_Jump = 1;
						if (Server()->Tick() % 4 == 0)
						{
							m_Input.m_Jump = 0;
						}
					}
				}

				//survival moves above the second freeze in the ruler from the left
				// ascii art shows where :
				//
				//                   |
				//                   |
				//                   v
				//                        --------
				//-----#####----###########-######
				//###########-####################
				//           #
				//           #
				//           -#########################----------
				//           #--------------------------

				if (m_Core.m_Pos.x > 439 * 32 && m_Core.m_Pos.x < 449 * 32)
				{
					//low left lowspeed --> go left
					if (m_Core.m_Pos.x > 439 * 32 && m_Core.m_Pos.y > 209 * 32 && m_Core.m_Vel.x < 3.0f)
					{
						m_Input.m_Direction = -1;
					}
					//low left highrightspeed --> go right with the speed and activate some random modes to keep the speed xD
					if (m_Core.m_Pos.x > 439 * 32 && m_Core.m_Pos.y > 209 * 32 && m_Core.m_Vel.x > 6.0f && m_Core.m_Jumped < 2)
					{
						m_Input.m_Direction = 1;
						m_Input.m_Jump = 1;
						if (Server()->Tick() % 5 == 0)
						{
							m_Input.m_Jump = 0;
						}
						m_Dummy_speedright = true;
					}

					if (isFreezed || m_Core.m_Vel.x < 4.3f)
					{
						m_Dummy_speedright = false;
					}

					if (m_Dummy_speedright)
					{
						m_Input.m_Direction = 1;
						m_Input.m_TargetX = 200;
						int r = rand() % 200 - 100;
						m_Input.m_TargetY = r;
						m_Input.m_Hook = 1;
						if (Server()->Tick() % 30 == 0 && m_Core.m_HookState != HOOK_GRABBED)
						{
							m_Input.m_Hook = 0;
						}
					}
				}
				else //out of the freeze area resett bools
				{
					m_Dummy_speedright = false;
				}



				//go down on plattform to get dj 
				//bot always fails going back from right
				//because he doesnt refills his dj

				//            |
				//            |
				//            v
				//                        --------
				//-----#####----###########-######
				//###########-####################
				//           #
				//           #
				//           -#########################----------
				//           #--------------------------

				if (m_Core.m_Pos.x > 433 * 32 + 20 && m_Core.m_Pos.x < 437 * 32 && m_Core.m_Jumped > 2)
				{
					m_Input.m_Direction = 1;
				}




				//##########################################
				// S P E C I A L    S H I T ! ! !          #
				//##########################################             agian...

				//woo special late important new stuff xD
				//reached hammerfly plattform --> get new movement skills
				//this area has his own extra codeblock with cool stuff

				if (m_Core.m_Pos.x > 448 * 32)
				{
					m_Input.m_Hook = 0;
					m_Input.m_Jump = 0;
					m_Input.m_Direction = 0;
					m_LatestInput.m_Fire = 0;
					m_Input.m_Fire = 0;

					if (m_Core.m_Pos.x < 451 * 32 + 20 && IsGrounded() == false && m_Core.m_Jumped > 2)
					{
						m_Input.m_Direction = 1;
					}
					if (m_Core.m_Vel.x < -0.8f && m_Core.m_Pos.x < 450 * 32 && IsGrounded())
					{
						m_Input.m_Jump = 1;
					}
					CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{
						if (m_Core.m_Pos.x < 451 * 32)
						{
							m_Input.m_Direction = 1;
						}

						if (pChr->m_Pos.x < m_Core.m_Pos.x - 7 * 32 && m_Core.m_Jumped < 2) //if enemy is on the left & bot has jump --> go left too
						{
							m_Input.m_Direction = -1;
						}
						if (m_Core.m_Pos.x > 454 * 32)
						{
							m_Input.m_Direction = -1;
							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

							if (m_Core.m_Pos.y + 40 > pChr->m_Pos.y)
							{
								m_Input.m_Hook = 1;
								if (Server()->Tick() % 50 == 0)
								{
									m_Input.m_Hook = 0;
								}
							}
						}


						//second freeze from the right --> goto singel palttform
						if (m_Core.m_Pos.x > 464 * 32 && m_Core.m_Jumped > 2 && m_Core.m_Pos.x < 468 * 32)
						{
							m_Input.m_Direction = 1;
						}
						//go back
						if (m_Core.m_Pos.x < 468 * 32 && IsGrounded() && m_Core.m_Pos.x > 464 * 32)
						{
							m_Input.m_Jump = 1;
						}
						//balance
						if (m_Core.m_Pos.x > 460 * 32 && m_Core.m_Pos.x < 464 * 32 && m_Core.m_Pos.y > 210 * 32 + 10)
						{
							m_Dummy_doBalance = true;
						}
						if (IsGrounded() && isFreezed)
						{
							m_Dummy_doBalance = false;
						}

						if (m_Dummy_doBalance)
						{
							if (m_Core.m_Pos.x > 463 * 32) //go right
							{
								if (m_Core.m_Pos.x > pChr->m_Pos.x - 4)
								{
									m_Input.m_Direction = -1;
								}
								else if (m_Core.m_Pos.x > pChr->m_Pos.x)
								{
									m_Input.m_Direction = 1;
								}

								if (m_Core.m_Pos.x < pChr->m_Pos.x)
								{
									m_Input.m_TargetX = 5;
									m_Input.m_TargetY = 200;
									if (m_Core.m_Pos.x - 1 < pChr->m_Pos.x)
									{
										m_Input.m_Fire++;
										m_LatestInput.m_Fire++;
									}
								}
								else
								{
									//do the random flick
									int r = rand() % 100 - 50;
									m_Input.m_TargetX = r;
									m_Input.m_TargetY = -200;
								}
								if (pChr->m_Pos.x > 465 * 32 - 10 && pChr->m_Pos.x < 469 * 32) //right enough go out
								{
									m_Input.m_Direction = 1;
								}


							}
							else //go left
							{
								if (m_Core.m_Pos.x > pChr->m_Pos.x + 4)
								{
									m_Input.m_Direction = -1;
								}
								else if (m_Core.m_Pos.x < pChr->m_Pos.x)
								{
									m_Input.m_Direction = 1;
								}

								if (m_Core.m_Pos.x > pChr->m_Pos.x)
								{
									m_Input.m_TargetX = 5;
									m_Input.m_TargetY = 200;
									if (m_Core.m_Pos.x + 1 > pChr->m_Pos.x)
									{
										m_Input.m_Fire++;
										m_LatestInput.m_Fire++;
									}
								}
								else
								{
									//do the random flick
									int r = rand() % 100 - 50;
									m_Input.m_TargetX = r;
									m_Input.m_TargetY = -200;
								}
								if (pChr->m_Pos.x < 459 * 32) //left enough go out
								{
									m_Input.m_Direction = -1;
								}
							}
						}

					}
					else //no close enemy alive
					{
						if (m_Core.m_Jumped < 2)
						{
							m_Input.m_Direction = -1;
						}
					}

					//jump protection second freeze from the right

					//                                  |            -########
					//                                  |            -########
					//                                  v                    #
					//                                                       #
					//                -------------##########---##############
					// ...#####---#######-########------------ ---------------

					if (m_Core.m_Pos.x > 458 * 32 && m_Core.m_Pos.x < 466 * 32)
					{
						if (m_Core.m_Pos.y > 211 * 32 + 26)
						{
							m_Input.m_Jump = 1;
						}
						if (m_Core.m_Pos.y > 210 * 32 && m_Core.m_Vel.y > 5.4f)
						{
							m_Input.m_Jump = 1;
						}
					}

					//go home if its oky, oky?
					if (m_Core.m_Pos.x < 458 * 32 && IsGrounded() && pChr->isFreezed || m_Core.m_Pos.x < 458 * 32 && IsGrounded() && pChr->m_Pos.x > m_Core.m_Pos.x + (10 * 32))
					{
						m_Input.m_Direction = -1;
					}
					//keep going also in the air xD
					if (m_Core.m_Pos.x < 450 * 32 && m_Core.m_Vel.x < 1.1f && m_Core.m_Jumped < 2)
					{
						m_Input.m_Direction = -1;
					}



					//                                           |   -########
					//                                           |   -########
					//                                           v           #
					//                                                       #
					//                -------------##########---##############
					// ...#####---#######-########------------ ---------------

					//go back if too far
					if (m_Core.m_Pos.x > 468 * 32 + 20)
					{
						m_Input.m_Direction = -1;
					}

				}


				//shitty nub like jump correction because i am too lazy too fix bugsis
				//T0D0(done): fix this bugsis
				//the bot jumps somehow at spawn if a player is in the ruler area
				//i was working with dummybored and tricks 
				//because i cant find the bug i set jump to 0 at spawn

				//here is ChillerDragon from ze future!
				// FUCK YOU old ChillerDragon you just wasted my fucking time with this shitty line
				//im working on another movement where i need jumps at spawn and it took me 20 minutes to find this shitty line u faggot!
				//wow ofc the bot does shit at spawn because u only said the ruler area is (m_Core.m_Pos.y < 213 * 32) and no check on X omg!
				//hope this wont happen agian! (talking to you future dragon)
				
				//if (m_Core.m_Pos.x < 407 * 32)
				//{
				//	m_Input.m_Jump = 0;
				//}


			}
			else //Change to mode main and reset all
			{
				GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "EROOR!!!!");
				//RestOnChange (zuruecksetzten)
				m_Input.m_Hook = 0;
				m_Input.m_Jump = 0;
				m_Input.m_Direction = 0;
				m_LatestInput.m_Fire = 0;
				m_Input.m_Fire = 0;



				m_Dummy_mode18 = 0;
			}

		}
		else if (m_pPlayer->m_DummyMode == 30) //ChillBlock5 the down left balance to secret moneyroom
		{
			//rest dummy 
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			//hardcodetselfkills:
			if (m_Core.m_Pos.x > 404 * 32)
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}
			if (m_Core.m_Pos.y < 204 * 32)
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}
			if (m_Core.m_Pos.y < 215 * 32 && m_Core.m_Pos.x < 386 * 32 - 3)
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}
			//selfkill
			//dyn
			if (m_Core.m_Vel.y == 0.000000f && m_Core.m_Vel.x < 0.01f && m_Core.m_Vel.x > -0.01f && isFreezed)
			{
				if (Server()->Tick() % 20 == 0)
				{
					GameServer()->SendEmoticon(m_pPlayer->GetCID(), 3);
				}

				if (Server()->Tick() % 90 == 0)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}
			}


			//balance
			CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
			if (pChr && pChr->IsAlive())
			{
				//m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				//m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
				//m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				//m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
				m_Input.m_TargetX = 2;
				m_Input.m_TargetY = 200;
				m_LatestInput.m_TargetX = 2;
				m_LatestInput.m_TargetY = 200;
				
				if (pChr->m_Pos.y > m_Core.m_Pos.y && m_Core.m_Pos.x > 310 * 32)
				{
					m_Input.m_Direction = 1;
					if (pChr->m_Pos.x < m_Core.m_Pos.x - 3)
					{
						m_Input.m_Direction = -1;
					}
					if (pChr->m_Pos.x > m_Core.m_Pos.x + 1)
					{
						m_Input.m_Direction = 1;
					}
					if (m_Core.m_Pos.x > pChr->m_Pos.x + 1 && m_Core.m_Pos.y > 238 * 32 && pChr->IsGrounded() && m_Core.m_Vel.x < -0.002f)
					{
						m_Input.m_Fire++;
						m_LatestInput.m_Fire++;
						m_Input.m_Direction = -1;
					}
				}
			}


			//movement going down#
			if (m_Core.m_Pos.y < 238 * 32 && m_Core.m_Pos.x > 344 * 32)
			{
				if (m_Core.m_Pos.x > 390 * 32)
				{
					m_Input.m_Direction = -1;
				}
				if (m_Core.m_Pos.x < 388 * 32)
				{
					m_Input.m_Direction = 1;
				}
			}
			else
			{
				if (Server()->Tick() % 40 == 0)
				{
					SetWeapon(0);
				}
			}


			if (m_Core.m_Pos.x < 314 * 32 - 10 && m_Core.m_Vel.x < -0.001f)
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
					m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

					if (m_Core.m_Pos.x > 310 * 32)
					{
						m_Input.m_Jump = 1;
					}
					if (m_Core.m_Pos.x > 305 * 32)
					{
						m_Input.m_Direction = -1;
					}
					if (m_Core.m_Pos.x < 308 * 32 + 10 && pChr->m_FreezeTime > 0)
					{
						m_Input.m_Hook = 1;
					}
				}
			}

		}
		else if (m_pPlayer->m_DummyMode == 31) //ChillBlock5 Police Guard
		{
			//rest dummy 
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			//Basic Stuff:
			//tele from spawn into police base
			if (m_Core.m_Pos.x < 410 * 32 && m_Core.m_Pos.x > 380 * 32 && m_Core.m_Pos.y < 219 * 32 && m_Core.m_Pos.y > 200 * 32) //spawn area
			{
				m_Core.m_Pos.x = 484 * 32;
				m_Core.m_Pos.y = 234 * 32;
				m_Dummy_SpawnAnimation = true;
			}
			//do spawnanimation in police base
			if (m_Dummy_SpawnAnimation)
			{
				m_Dummy_SpawnAnimation_delay++;
				if (m_Dummy_SpawnAnimation_delay > 2)
				{
					GameServer()->CreatePlayerSpawn(m_Pos);
					m_Dummy_SpawnAnimation = false;
				}
			}

			//selfkill
			//dyn
			if (m_Core.m_Vel.y == 0.000000f && m_Core.m_Vel.x < 0.01f && m_Core.m_Vel.x > -0.01f && isFreezed)
			{
				if (Server()->Tick() % 20 == 0)
				{
					GameServer()->SendEmoticon(m_pPlayer->GetCID(), 3);
				}

				if (Server()->Tick() % 200 == 0)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}
			}



			//TODO:
			/*
			Check for an officör acteevated the "help me in base" bool
			m_IsHelpPolice = -1;


			for (int i = 0; i++; i < MAX_CLIENTS)
			{
				if (m_HelpPolice)
					m_IsHelpPolice = i; //return id
			}
			
			if (m_isHelpPolice)
			{

					//geh den suchen und hilf dem usw

			}
			
			
			*/


			CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true); 
			if (pChr && pChr->IsAlive())
			{
				//for (int i = 0; i < MAX_CLIENTS; i++)
				//{
				//	if (p)
				//}
				m_Dummy_ClosestPolice = false;
				//If a policerank escapes from jail he is treated like a non police
				if (pChr->m_pPlayer->m_PoliceRank > 0 && pChr->m_pPlayer->m_EscapeTime == 0 || pChr->m_pPlayer->m_PoliceHelper && pChr->m_pPlayer->m_EscapeTime == 0)
				{
					//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "hello officör");
					m_Dummy_ClosestPolice = true;
					//if (pChr->isFreezed)
					//{
					//	m_Dummy_dmm31 = 2;
					//}
				}

				/*
				########################################

				m_Dummy_dmm31 - - - DUMMY MODE MODE [31]

				########################################

				Structure:

				* [STRUC][1]: Check what sub-mode shoudl be used 

				* [STRUC][2]: Do stuff depending on sub-modes

				* [STRUC][3]: Do basic movement depending on sub-modes ( step 2 for all modes higher than 3)


				modes:

				0				LOCAL: NOTHING IS GOING ON
				1				LOCAL: ENEMY ATTACK
				2				LOCAL: POLICE HELP
				3				EXTERNAL: ENEMY ATTACK (right side / jail side)
				4				EXTERNAL: POLICE HELP (right side / jail side)

				*/

				//##############################################
				//[STRUC][1]: Check what sub-mode shoudl be used 
				//##############################################
				if (m_Dummy_ClosestPolice) //police
				{
					if (pChr->m_FreezeTime > 0 && m_Core.m_Pos.x < 477 * 32)
					{
						m_Dummy_dmm31 = 2; // LOCAL: POLICE HELP
					}
					else
					{
						m_Dummy_dmm31 = 0; // LOCAL: NOTHING IS GOING ON
					}
				}
				else //not police
				{
					if (pChr->m_FreezeTime == 0)
					{
						if (pChr->m_Pos.x > 481 * 32)
						{
							//m_Dummy_dmm31 = 3; //EXTERNAL: ENEMY ATTACK(right side / jail side)
						}
						else
						{
							m_Dummy_dmm31 = 1; //LOCAL: ENEMY ATTACK
						}
					}
					if (pChr->isFreezed)
					{
						m_Dummy_dmm31 = 0; //maybe add here a mode where the bot moves the nonPolices away to find failed polices
					}
				}


				//##############################################
				//[STRUC][2]: Do stuff depending on sub - modes
				//##############################################

				if (m_Dummy_dmm31 == 0) //nothing is going on
				{
					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
					m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
					if (Server()->Tick() % 90 == 0)
					{
						SetWeapon(1);
					}
				}
				else if (m_Dummy_dmm31 == 1) //Attack enemys
				{
					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
					m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;


					if (Server()->Tick() % 30 == 0)
					{
						SetWeapon(0);
					}

					if (m_FreezeTime == 0 && pChr->m_FreezeTime == 0 && pChr->m_Core.m_Vel.y < -0.5 && pChr->m_Pos.x > m_Core.m_Pos.x - 3 * 32 && pChr->m_Pos.x < m_Core.m_Pos.x + 3 * 32)
					{
						m_Input.m_Fire++;
						m_LatestInput.m_Fire++;
					}

					m_Dummy_AttackMode = 0;
					if (m_Core.m_Pos.x < 466 * 32 + 20 && pChr->m_Pos.x > 469 * 32 + 20) //hook enemy in air (rightside)
					{
						m_Dummy_AttackMode = 1;
					}

					if (m_Dummy_AttackMode == 0) //default mode
					{
						if (m_Core.m_Pos.x < 466 * 32 - 5) //only get bored on lovley place 
						{
							m_Input.m_Direction = rand() % 2;
							if (IsGrounded())
							{
								m_Input.m_Jump = rand() % 2;
							}
							if (pChr->m_Pos.y > m_Core.m_Pos.y)
							{
								m_Input.m_Hook = 1;
							}
						}
					}
					else if (m_Dummy_AttackMode == 1) //hook enemy escaping (rightside)
					{
						if (pChr->m_Core.m_Vel.x > 1.3f)
						{
							m_Input.m_Hook = 1;
						}
					}


					//Dont Hook enemys back in safety
					if (pChr->m_Pos.x < 460 * 32 && pChr->m_Pos.x >	457 * 32 || pChr->m_Pos.x < 469 * 32 && pChr->m_Pos.x >	466 * 32)
					{
						m_Input.m_Hook = 0;
					}

				}
				else if (m_Dummy_dmm31 == 2) //help police dudes
				{
					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
					m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;

					if (pChr->m_Pos.y > m_Core.m_Pos.y)
					{
						m_Input.m_Hook = 1;
					}
					if (Server()->Tick() % 40 == 0)
					{
						m_Input.m_Hook = 0;
						m_Input.m_Jump = 0;
					}
					if (IsGrounded() && pChr->isFreezed)
					{
						m_Input.m_Jump = 1;
					}

					if (pChr->isFreezed)
					{
						if (pChr->m_Pos.x > m_Core.m_Pos.x)
						{
							m_Input.m_Direction = 1;
						}
						else if (pChr->m_Pos.x < m_Core.m_Pos.x)
						{
							m_Input.m_Direction = -1;
						}
					}
					else
					{
						if (pChr->m_Pos.x - 110 > m_Core.m_Pos.x)
						{
							m_Input.m_Direction = 1;
						}
						else if (pChr->m_Pos.x + 110 < m_Core.m_Pos.x)
						{
							m_Input.m_Direction = -1;
						}
						else
						{
							if (Server()->Tick() % 10 == 0)
							{
								SetWeapon(0);
							}
							if (m_FreezeTime == 0 && pChr->m_FreezeTime > 0)
							{
								m_Input.m_Fire++;
								m_LatestInput.m_Fire++;
							}
						}
					}


					//invert direction if hooked the player to add speed :)
					if (m_Core.m_HookState == HOOK_GRABBED)
					{
						if (pChr->m_Pos.x > m_Core.m_Pos.x)
						{
							m_Input.m_Direction = -1;
						}
						else if (pChr->m_Pos.x < m_Core.m_Pos.x)
						{
							m_Input.m_Direction = 1;
						}
					}

					//schleuderprotection   stop hook if mate is safe to prevemt blocking him to the other side
					if (pChr->m_Pos.x > 460 * 32 + 10 && pChr->m_Pos.x < 466 * 32)
					{
						m_Input.m_Hook = 0;
					}

				}
				else if (m_Dummy_dmm31 == 3) //EXTERNAL: Enemy attack (rigt side /jail side)
				{
					if (m_Core.m_Pos.x < 461 * 32)
					{
						m_Input.m_Direction = 1;
					}
					else
					{
						if (m_Core.m_Pos.x < 484 * 32)
						{
							m_Input.m_Direction = 1;
						}
						if (m_Core.m_Pos.x > 477 * 32 && !IsGrounded())
						{
							m_Input.m_Hook = 1;
						}
					}

					//jump all the time xD
					if (IsGrounded() && m_Core.m_Pos.x > 480 * 32)
					{
						m_Input.m_Jump = 1;
					}

					//Important jump protection
					if (m_Core.m_Pos.x > 466 * 32 && m_Core.m_Pos.y > 240 * 32 + 8 && m_Core.m_Pos.x < 483 * 32)
					{
						m_Input.m_Jump = 1;
					}
				}
				else //unknown dummymode
				{
					m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
					m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
					m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
					if (Server()->Tick() % 120 == 0)
					{
						//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "error: unknow sub-mode for this dummymode set.");
					}
				}

			}





			//##############################################
			//[STRUC][3]: Do basic movement depending on sub - modes
			//##############################################

			//The basic movements depending on the dummysubmodes 
			//but some submodes use the same thats why its listed external here
			//Movement
			//JailSpawn
			if (m_Dummy_dmm31 < 3)
			{
				if (m_Core.m_Pos.x > 482 * 32 + 20 && m_Core.m_Pos.y < 236 * 32)
				{
					if (m_Core.m_Vel.x > -8.2f && m_Core.m_Pos.x < 484 * 32 - 20)
					{
						m_Dummy_GetSpeed = true;
					}
					if (m_Core.m_Pos.x > 483 * 32 && !IsGrounded())
					{
						m_Dummy_GetSpeed = true;
					}
					if (m_Core.m_Vel.y > 5.3f)
					{
						m_Dummy_GetSpeed = true;
					}

					if (IsGrounded() && m_Core.m_Pos.x > 485 * 32)
					{
						m_Dummy_GetSpeed = false;
					}



					if (m_Dummy_GotStuck)
					{
						m_Input.m_Direction = -1;
						if (Server()->Tick() % 33 == 0)
						{
							m_Input.m_Jump = 1;
						}
						if (Server()->Tick() % 20 == 0)
						{
							SetWeapon(0); //hammer
						}

						if (m_Input.m_TargetX < -20)
						{
							if (m_FreezeTime == 0)
							{
								m_Input.m_Fire++;
								m_LatestInput.m_Fire++;
							}
						}
						else if (m_Input.m_TargetX > 20)
						{
							m_Input.m_Hook = 1;
							if (Server()->Tick() % 25 == 0)
							{
								m_Input.m_Hook = 0;
							}
						}

						//gets false in the big esle m_Dummy_GotStuck = false;
					}
					else
					{
						if (m_Dummy_GetSpeed)
						{
							m_Input.m_Direction = 1;
							if (Server()->Tick() % 90 == 0)
							{
								m_Dummy_GotStuck = true;
							}
						}
						else
						{
							m_Input.m_Direction = -1;
							if (m_Core.m_Vel.x > -4.4f)
							{
								if (Server()->Tick() % 90 == 0)
								{
									m_Dummy_GotStuck = true;
								}
							}
						}
					}

				}
				else //not Jail spawn
				{
					m_Dummy_GotStuck = false;
					//TODO; add a dir 1 if he gets attacked
					if (m_Core.m_Pos.x > 464 * 32)
					{
						m_Input.m_Direction = -1;
					}
					else if (m_Core.m_Pos.x < 461 * 32)
					{
						m_Input.m_Direction = 1;
					}

					if (m_Core.m_Pos.x > 466 * 32 && m_Core.m_Pos.y > 240 * 32 + 8)
					{
						m_Input.m_Jump = 1;
					}
				}
			}
			else
			{
				//no basic moves for this submode
			}
		}
		else if (m_pPlayer->m_DummyMode == 32) //chattin guy
		{
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;
			m_Dummy_32tick++;

			if (m_Dummy_32reset)
			{
				m_Dummy_32weapon = 0;
				m_Dummy_32balance = 0;
				m_Dummy_32dir = 0;
				m_Dummy_32fire = false;
				m_Dummy_32jump = false;
				m_Dummy_32hook = false;
				m_pPlayer->m_Dummy_32dummy = false;
				m_Dummy_32reset = false;
			}

			//DIRECTION
			m_Input.m_Direction = m_Dummy_32dir;

			//WEAPONS
			if (m_aWeapons[m_Dummy_32weapon].m_Got)
			{
				SetWeapon(m_Dummy_32weapon);
			}


			//SELFKILL
			if (m_Dummy_32kill)
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}

			//FIRE
			if (m_Dummy_32fire || m_Dummy_32tick > m_Dummy_32fire0_start && m_Dummy_32tick < m_Dummy_32fire0_stop)
			{
				m_Input.m_Fire++;
			}

			//JUMP
			if (m_Dummy_32jump)
			{
				m_Input.m_Jump = 1;
			}

			//HOOK
			if (m_Dummy_32hook)
			{
				m_Input.m_Hook = 1;
			}

			//FIRE
			if (m_Dummy_32fire)
			{
				m_Input.m_Fire++;
				m_LatestInput.m_Fire++;
			}

			//LOOK
			if (m_pPlayer->m_Dummy_32look == 0) //right
			{
				m_Input.m_TargetX = 200;
				m_Input.m_TargetY = 2;
				m_LatestInput.m_TargetX = 200;
				m_LatestInput.m_TargetY = 2;
			}
			else if (m_pPlayer->m_Dummy_32look == 1) //down
			{
				m_Input.m_TargetX = 1;  
				m_Input.m_TargetY = 200;
				m_LatestInput.m_TargetX = 1;
				m_LatestInput.m_TargetY = 200;
			}
			else if (m_pPlayer->m_Dummy_32look == 2) //left
			{
				m_Input.m_TargetX = -200;
				m_Input.m_TargetY = 2;
				m_LatestInput.m_TargetX = -200;
				m_LatestInput.m_TargetY = 2;
			}
			else if (m_pPlayer->m_Dummy_32look == 2) //up
			{
				m_Input.m_TargetX = 1;
				m_Input.m_TargetY = -200;
				m_LatestInput.m_TargetX = 1;
				m_LatestInput.m_TargetY = -200;
			}

			//BALANCE
			if (m_Dummy_32balance == 1) //middle
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					if (pChr->m_Pos.y > m_Core.m_Pos.y)
					{
						if (pChr->m_Pos.x > m_Core.m_Pos.x + 2)
						{
							m_Input.m_Direction = 1;
						}
						else if (pChr->m_Pos.x < m_Core.m_Pos.x - 2)
						{
							m_Input.m_Direction = -1;
						}
					}
				}
			}
			else if (m_Dummy_32balance == 2) //left
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					m_Input.m_TargetX = 2;
					m_Input.m_TargetY = 200;
					m_LatestInput.m_TargetX = 2;
					m_LatestInput.m_TargetY = 200;

					if (pChr->m_Pos.y > m_Core.m_Pos.y)
					{
						m_Input.m_Direction = 1;
						if (pChr->m_Pos.x < m_Core.m_Pos.x - 3)
						{
							m_Input.m_Direction = -1;
						}
						if (pChr->m_Pos.x > m_Core.m_Pos.x + 1)
						{
							m_Input.m_Direction = 1;
						}
						if (m_Core.m_Pos.x > pChr->m_Pos.x + 1 && pChr->IsGrounded() && m_Core.m_Vel.x < -0.002f)
						{
							m_Input.m_Fire++;
							m_LatestInput.m_Fire++;
							m_Input.m_Direction = -1;
						}
					}
				}
			}
			else if (m_Dummy_32balance == 3) //right
			{
				CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
				if (pChr && pChr->IsAlive())
				{
					m_Input.m_TargetX = -2;
					m_Input.m_TargetY = 200;
					m_LatestInput.m_TargetX = -2;
					m_LatestInput.m_TargetY = 200;

					if (pChr->m_Pos.y > m_Core.m_Pos.y)
					{
						m_Input.m_Direction = -1;
						if (pChr->m_Pos.x > m_Core.m_Pos.x + 3)
						{
							m_Input.m_Direction = 1;
						}
						if (pChr->m_Pos.x < m_Core.m_Pos.x - 1)
						{
							m_Input.m_Direction = -1;
						}
						if (m_Core.m_Pos.x < pChr->m_Pos.x - 1 && pChr->IsGrounded() && m_Core.m_Vel.x > 0.002f)
						{
							m_Input.m_Fire++;
							m_LatestInput.m_Fire++;
							m_Input.m_Direction = 1;
						}
					}
				}
			}

			//Dummy == true ---> walk to block area
			if (m_pPlayer->m_Dummy_32dummy)
			{
				//hardcodet selfkills:
				if (m_Core.m_Pos.x < 392 * 32 || m_Core.m_Pos.y > 219 * 32 + 5 && m_Core.m_Pos.x < 416 * 32 || m_Core.m_Pos.y > 223 * 32)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}

				if (m_Core.m_Pos.x < 420 * 32 || m_Core.m_Pos.y > 214 * 32)
				{
					m_Input.m_Direction = 1;
				}

				//jumps
				if (IsGrounded() && m_Core.m_Pos.x > 403 * 32 && m_Core.m_Pos.x < 410 * 32 || m_Core.m_Pos.y < 209 * 32)
				{
					m_Input.m_Jump = 1;
				}

				if (m_Core.m_Pos.x > 453 * 32)
				{
					m_Input.m_Direction = -1;
				}

			}

		}
		else if (m_pPlayer->m_DummyMode == 33) //ChillBlock5 left block area
		{
			//rest dummy 
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			//~~~~~~~~~
			//selfkill
			//~~~~~~~~~
			//dynanimc
			if (m_Core.m_Pos.x > 331 * 32 && m_Core.m_Pos.x < 371 * 32 && m_Core.m_Pos.y > 197 * 32 && m_Core.m_Pos.y < 220 * 32)
			{
				//the bot is happy even if he is freeze he is in his loved blockarea
			}
			else //else --> dyn kill
			{
				if (m_Core.m_Vel.y == 0.000000f && m_Core.m_Vel.x < 0.01f && m_Core.m_Vel.x > -0.01f && isFreezed)
				{
					if (Server()->Tick() % 20 == 0)
					{
						GameServer()->SendEmoticon(m_pPlayer->GetCID(), 3);
					}

					if (m_Core.m_Pos.x < 376 * 32) //far
					{
						if (Server()->Tick() % 190 == 0)
						{
							Die(m_pPlayer->GetCID(), WEAPON_SELF);
						}
					}
					else  //not far
					{
						if (Server()->Tick() % 50 == 0)
						{
							Die(m_pPlayer->GetCID(), WEAPON_SELF);
						}
					}
				}
			}
			//hardcodet
			if (m_Core.m_Pos.x > 405 * 32) //spawn left
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}
			if (m_Core.m_Pos.y > 218 * 32) //too low for example spawn down
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}

			//~~~~~~~~~~
			//Movement
			//~~~~~~~~~~

			//right side of the freeze (spawn n stuff)
			if (m_Core.m_Pos.x > 364 * 32)
			{
				m_Input.m_Direction = -1;
				//1st ground jump
				if (m_Core.m_Pos.x < 392 * 32 && IsGrounded())
				{
					m_Input.m_Jump = 1;
				}

				//2nd air jump
				if (m_Core.m_Pos.y > 216 * 32 - 10)
				{
					m_Input.m_Jump = 1;
				}


				if (m_Core.m_Pos.x < 373 * 32)
				{
					CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{
						m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
						m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
						m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
						m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;


					}
				}


			}

		}
		else if (m_pPlayer->m_DummyMode == 99) //finally the special one :)
		{
			//rest dummy 
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 1;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;



			/*
			Plans for this mode:
			make the bot predict the future:
			-plans
			-fear
			-realistic 

			then let the bot choose what is the best way to maximize his happyness:
			calculate what to do:
			- make plans come true
			- make fear dont come true
			- prepare for what will happen pretty sure
			*/

			

			CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true); 
			if (pChr && pChr->IsAlive())
			{
				//m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				//m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
				//m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
				//m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;



				//check for teetower
				if (pChr->m_Pos.x > m_Core.m_Pos.x - 2 && pChr->m_Pos.x < m_Core.m_Pos.x + 2 && pChr->m_Pos.y > m_Core.m_Pos.y - 128 && pChr->m_Pos.y < m_Core.m_Pos.y + 128)
				{
					m_pPlayer->m_TeeInfos.m_ColorBody = (360 * 200 / 360);

					if (pChr->m_Pos.y > m_Core.m_Pos.y)
					{

					}
					else if (pChr->m_Pos.y < m_Core.m_Pos.y)
					{

					}
				}
				else
				{
					//m_pPlayer->m_TeeInfos.m_ColorBody = (0 * 255 / 360);
					m_pPlayer->m_TeeInfos.m_ColorBody = (0 * 255 / 360);
				}
			}

		}
		else if (m_pPlayer->m_DummyMode == 100) //xyz_ddrace2 (ChillerEdited version)
		{
			//rest dummy 
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;
			/*
			DummyMode 100!
			from here the dummy modes that are made for maps not by ChillerDragon start.

			i edited the xyz_ddrace2 a bit to have more space up and to the right
			---> i used a var in the code to change between normal xyz_ddrace2 and xyz_ddrace2 (edited by Chiller)

			x_correction = 0
			y_correction = 0

			use something around this to use the dummymode on the normal version

			x 100
			y 100
			
			*/
			int x_correction = 0 * 32; //100 * 32 to use other map versions
			int y_correction = 0 * 32; //100 * 32 to use other map versions


			//hardcodetselfkills:
			if (m_Core.m_Pos.x < 122 * 32 - x_correction && m_Core.m_Pos.y > 119 * 32 - y_correction && isFreezed && m_Core.m_Vel.y == 0.0f)
			{
				if (Server()->Tick() % 20 == 0)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}
			}

			//Spawn area: spawn left, downspawn right and downspawndown
			if (m_Core.m_Pos.x < 141 * 32 - x_correction && m_Core.m_Pos.y < 139 * 32 - y_correction)
			{
				if (m_Core.m_Pos.y > 112 * 32 - y_correction)
				{
					m_Dummy_isSpawnArea = false;
				}

				if (m_Dummy_isSpawnArea)
				{
					if (m_Core.m_Pos.x > 105 * 32 - x_correction)
					{
						m_Input.m_Direction = -1;
						m_Input.m_TargetX = 56;
						m_Input.m_TargetY = -4;
					}
				}
				else //not spawn area
				{
					m_Input.m_TargetX = -100;
					m_Input.m_TargetY = -200;
					m_Input.m_Direction = 1;

					if (m_Core.m_Pos.x < 108 * 32 - x_correction)
					{
						if (m_Core.m_Pos.y > 112 * 32 + 56 - y_correction)
						{
							m_Dummy_100hook = true;
						}
						if (m_Core.m_Pos.x > 108 * 32 - 10 - x_correction)
						{
							m_Dummy_100hook = false;
						}


						if (m_Dummy_100hook)
						{
							m_Input.m_Hook = 1;
						}
						else
						{
							m_Dummy_100hook = 0;
						}
					}
					else //x > 108
					{
						if (m_Core.m_Pos.x < 131 * 32 - x_correction)
						{
							m_Input.m_TargetX = 125;
							m_Input.m_TargetY = 200;
							if (m_Core.m_Pos.y > 115 * 32 - y_correction)
							{
								m_Dummy_100hook = true;
							}
							if (m_Core.m_Pos.y > 117 * 32 - y_correction && m_Core.m_Pos.x < 131 * 32 - x_correction)
							{
								m_Dummy_100hook = false;
								m_Input.m_Jump = 1;
							}

							if (m_Core.m_Jumped < 2 && m_Dummy_100hook)
							{
								m_Input.m_Hook = 1;
							}
						}

						//resett hook while walking underspawn & get speed by hooking ground
						if (m_Core.m_Pos.x > 123 * 32 - x_correction && m_Core.m_Pos.x < 130 * 32 - x_correction)
						{
							m_Input.m_TargetX = 200;
							m_Input.m_TargetY = 20;
							m_Input.m_Hook = 0;
							if (m_Dummy_100downstyle == 2)
							{
								if (m_Core.m_Pos.x > 123 * 32 + 10 - x_correction)
								{
									m_Input.m_Hook = 1;
								}
							}
							if (m_Core.m_Pos.x > 127 * 32 - x_correction)
							{
								m_Input.m_Hook = 0;
								m_Dummy_100hook = false;
								m_Input.m_TargetX = -67;
								m_Input.m_TargetY = 200;
							}
						}


						//down after first part (almost far xD)
						/*
						down struct:

						you can choose here between the old style (was far but not far enough)

						or the new testy way

						m_Dummy_100downstyle == 0 (old)
						m_Dummy_100downstyle == 1 (testy)
						m_Dummy_100downstyle == 2 (testy2 with speedhook)     WARNING! this mode has some changes in the resett hook code above

						*/

						m_Dummy_100downstyle = 2;

						if (m_Dummy_100downstyle == 0)
						{
							if (m_Core.m_Pos.x > 131 * 32 - x_correction && m_Core.m_Pos.y > 115 * 32 + 5 - y_correction)
							{
								m_Input.m_TargetX = -97;
								m_Input.m_TargetY = 200;

								//m_Input.m_Hook = 0;
								if (m_Core.m_Pos.y > 115 * 32 + 20 - y_correction && m_Core.m_Pos.y < 118 * 32 - y_correction)
								{
									//this hook is only used in m_Dummy_100downstyle == 1
									//m_Input.m_Hook = 1;
								}

								if (m_Core.m_Pos.y < 125 * 32 - y_correction)
								{
									if (m_Core.m_Pos.x > 134 * 32 - x_correction)
									{
										m_Input.m_Direction = -1;
									}
								}
								else // x > 125
								{
									if (m_Core.m_Pos.y < 128 * 32 - y_correction)
									{
										m_Input.m_Direction = -1;
									}
									else //y > 128
									{
										m_Input.m_Hook = 0;
										m_Input.m_Direction = 1;
										m_Input.m_TargetX = 200;
										m_Input.m_TargetY = -8;
										if (m_Core.m_Pos.y > 130 * 32 + 7 - y_correction)
										{
											m_Input.m_Hook = 1;
										}
									}
								}
							}
						}
						else if (m_Dummy_100downstyle == 1)
						{
							if (m_Core.m_Pos.x > 131 * 32 - x_correction && m_Core.m_Pos.y > 115 * 32 + 5 - y_correction)
							{
								m_Input.m_TargetX = -97;
								m_Input.m_TargetY = 200;

								//m_Input.m_Hook = 0;
								if (m_Core.m_Pos.y > 115 * 32 + 4 - y_correction && m_Core.m_Pos.y < 118 * 32 - y_correction)
								{
									m_Input.m_Hook = 1;
								}

								if (m_Core.m_Pos.y < 125 * 32 - y_correction)
								{
									if (m_Core.m_Pos.x > 134 * 32 - x_correction)
									{
										m_Input.m_Direction = -1;
									}
								}
								else // x > 125
								{
									if (m_Core.m_Pos.y < 128 * 32 + 29 - y_correction)
									{
										m_Input.m_Direction = -1;
									}
									else //y > 128 + 29
									{
										m_Input.m_Hook = 0;
										m_Input.m_Direction = 1;
										m_Input.m_TargetX = 200;
										m_Input.m_TargetY = -139;
										if (m_Core.m_Pos.y > 129 * 32 + 45 - y_correction)
										{
											m_Input.m_Hook = 1;
										}
									}
								}
							}
						}
						else if (m_Dummy_100downstyle == 2) //also has some external changes (boostystyle)
						{
							if (m_Core.m_Pos.x > 131 * 32 - x_correction && m_Core.m_Pos.y > 115 * 32 + 5 - y_correction)
							{
								m_Input.m_TargetX = -167;
								m_Input.m_TargetY = 200;

								//m_Input.m_Hook = 0;
								if (m_Core.m_Pos.y > 115 * 32 + 4 - y_correction && m_Core.m_Pos.y < 118 * 32 - y_correction)
								{
									m_Input.m_Hook = 1;
								}

								if (m_Core.m_Pos.y < 125 * 32 - y_correction)
								{
									if (m_Core.m_Pos.x > 134 * 32 - x_correction)
									{
										m_Input.m_Direction = -1;
									}
								}
								else // x > 125
								{
									if (m_Core.m_Pos.y < 128 * 32 + 29 - y_correction)
									{
										m_Input.m_Direction = -1;
									}
									else //y > 128 + 29
									{
										m_Input.m_Hook = 0;
										m_Input.m_Direction = 1;
										m_Input.m_TargetX = 200;
										m_Input.m_TargetY = -74;
										if (m_Core.m_Pos.y > 129 * 32 + 47 - y_correction)
										{
											m_Input.m_Hook = 1;
										}
									}
								}
							}
						}
					}
				}
			}
			else //not spawn area after insane solo jump swing xD
			{
				if (m_Core.m_Pos.y > 136 * 32 - y_correction && m_Core.m_Pos.x < 149 * 32 - x_correction || m_Core.m_Pos.y > 140 * 32 - y_correction && m_Core.m_Pos.x < 171 * 32 - x_correction) //tunnel with freeze floor
				{
					m_Input.m_Direction = 1;
					m_Input.m_TargetX = 90;
					m_Input.m_TargetY = -200;

					if (m_Core.m_Pos.y > 142 * 32 + 60 - y_correction || m_Core.m_Vel.y > 4.4f)
					{
						m_Input.m_Hook = 1;
					}

					if (m_Core.m_Pos.y < 142 * 32 + 50 - y_correction && m_Core.m_Pos.y > 141 * 32 + 31 - y_correction && m_Core.m_Pos.x < 161 * 32 - x_correction)
					{
						m_Input.m_TargetX = 210;
						m_Input.m_TargetY = 200;
						if (m_Core.m_Pos.y < 142 * 32 + 30 - y_correction && m_Core.m_Vel.y < 3.4f)
						{
							m_Input.m_Hook = 1;
						}
						else
						{
							m_Input.m_Hook = 0;
						}
					}

					//end go up
					if (m_Core.m_Pos.x > 166 * 32 - 20 - x_correction)
					{
						m_Input.m_TargetX = 40;
						m_Input.m_TargetY = -120;
						//m_Input.m_Hook = 0;
						if (m_Core.m_Pos.x > 166 * 32 + 20 - x_correction)
						{
							m_Input.m_Hook = 1;
						}
					}
				}
				else //Main part
				{
					if (m_Core.m_Pos.y > 129 * 32 - y_correction) //down area (mainpart)
					{
						if (m_Core.m_Pos.x > 159 * 32 + 5 - x_correction)
						{
							m_Input.m_Direction = -1;
							//Get Up (jump)
							if (m_Core.m_Pos.x > 160 * 32 - x_correction)
							{
								if (IsGrounded())
								{
									m_Input.m_Jump = 0;
									if (Server()->Tick() % 10 == 0)
									{
										m_Input.m_Jump = 1;
									}
								}
								else //not grounded --> get grounded
								{
									m_Input.m_TargetX = -200;
									m_Input.m_TargetY = 190;
									m_Input.m_Hook = 1;
									if (Server()->Tick() % 7 == 0)
									{
										m_Input.m_Hook = 0;
									}
								}
							}
						}

						/*
						m_Dummy_1002p_state Structy:

						classical 2p_state int usage u know mate?

						0			prepare
						1			go left with hook


						*/

						if (m_Dummy_1002p_state == 0)
						{
							//go on edge
							if (m_Core.m_Pos.x < 159 * 32 - x_correction && m_Core.m_Vel.y == 0.0f)
							{
								if (m_Core.m_Vel.x < 0.5f)
								{
									m_Input.m_Direction = 1;
								}
							}
							GameServer()->SendEmoticon(m_pPlayer->GetCID(), 1);
						}


						CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
						if (pChr && pChr->IsAlive())
						{

							//prepare aim to do the part
							if (m_Dummy_1002p_state == 0) //prepare
							{
								GameServer()->SendEmoticon(m_pPlayer->GetCID(), 2);
								//go on edge
								if (m_Core.m_Pos.x < 159 * 32 - x_correction && m_Core.m_Vel.y == 0.0f)
								{
									if (m_Core.m_Vel.x < 0.5f)
									{
										m_Input.m_Direction = 1;
									}
								}
								//if in position get aimy
								if (m_Core.m_Pos.x > 157 * 32 - x_correction && m_Core.m_Pos.x < 160 * 32 - x_correction)
								{
									m_Input.m_TargetX = 2;
									m_Input.m_TargetY = 200;
									/*							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
									m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
									m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
									m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;*/
									if (pChr->m_Pos.y > m_Core.m_Pos.y + 40 && pChr->m_Pos.x > m_Core.m_Pos.x - 60 && pChr->m_Pos.x < m_Core.m_Pos.x + 60)
									{
										//m_Input.m_Hook = 1;
										if (Server()->Tick() % 10 == 0)
										{
											m_Dummy_1002p_state = 1;
										}
									}

								}
							}
							else if (m_Dummy_1002p_state == 1) //go left
							{
								GameServer()->SendEmoticon(m_pPlayer->GetCID(), 3);
								m_Input.m_Hook = 1;
								m_Input.m_Direction = -1;
								if (pChr->m_Pos.x < 152 * 32 - 8 - x_correction)
								{
									m_Dummy_1002p_state = 2;
								}


								if (Server()->Tick() % 40 == 0)
								{
									//Check hook
									if (m_Core.m_HookState != HOOK_GRABBED)
									{
										m_Dummy_1002p_state = 0;
									}
									//wait some time and check wehre mate is
									if (pChr->m_Pos.x > 155 * 32 - x_correction || pChr->m_Pos.y < 137 * 32 - y_correction && pChr->m_Pos.x > 152 * 32 - x_correction)
									{
										//if his pos sucks --> restart
										m_Dummy_1002p_state = 0;
									}
								}
							}
							else if (m_Dummy_1002p_state == 2)
							{
								m_Input.m_Hook = 1;
								GameServer()->SendEmoticon(m_pPlayer->GetCID(), 4);
								if (m_Core.m_Pos.y > 134 * 32 - y_correction || m_Core.m_Pos.y < 132 * 32 - y_correction && m_Core.m_Vel.y > -0.84f)
								{
									m_Input.m_Jump = 1;
								}


								if (m_Core.m_Pos.y < 131 * 32 - y_correction)
								{
									m_Input.m_Hook = 0;
									m_Input.m_TargetX = -100;
									m_Input.m_TargetY = -190;
									if (m_Core.m_Pos.y < 129 * 32 + 3 - y_correction)
									{
										m_Dummy_1002p_hook = true;
										m_Input.m_Hook = 1;
									}
								}

								if (m_Dummy_1002p_hook)
								{
									m_Input.m_Hook = 1;
									if (Server()->Tick() % 40 == 0)
									{
										m_Dummy_1002p_hook = false;
									}
								}

								if (Server()->Tick() % 40 == 0)
								{
									//wait some time and check wehre mate is
									if (pChr->m_Pos.x > 155 * 32 - x_correction || pChr->m_Pos.y < 137 * 32 - y_correction && pChr->m_Pos.x > 152 * 32 - x_correction)
									{
										//if his pos sucks --> restart
										m_Dummy_1002p_state = 0;
									}
								}

							}
							else
							{
								m_Dummy_1002p_state = 0;
							}
						}




					}
					else //upper area (mainpart)
					{

					}
				}
			}




		}
		else if (m_pPlayer->m_DummyMode == 101) //touchup (blocker)
		{
			//rest dummy 
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			//selfkill
			if (m_Core.m_Vel.y == 0.000000f && m_Core.m_Vel.x < 0.01f && m_Core.m_Vel.x > -0.01f && isFreezed)
			{
				if (Server()->Tick() % 20 == 0)
				{
					GameServer()->SendEmoticon(m_pPlayer->GetCID(), 3);
				}

				if (Server()->Tick() % 90 == 0)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}
			}


			//emotes

			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();
				int r = rand() % 100;
				GameServer()->SendEmoticon(m_pPlayer->GetCID(), r < 10 ? 1 : r < 55 ? 10 : 9);

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() * 10 + Server()->TickSpeed() * (rand() % 21);
			}


			//focus the floor (flick is funny xD)
			m_Input.m_TargetX = -40;
			m_Input.m_TargetY = 200;


			//Movement
			if (m_Core.m_Pos.y < 62 * 32 && m_Core.m_Pos.x < 84 * 32 && m_Core.m_Pos.x > 60 * 32) //at spawn
			{
				m_Input.m_Direction = -1;
			}

			if (m_Core.m_Pos.y > 62 * 32 && m_Core.m_Pos.y < 70 * 32 + 5 && m_Core.m_Pos.x < 108 * 32 || m_Core.m_Pos.x < 83 * 32 && m_Core.m_Pos.y > 62 * 32 && m_Core.m_Pos.y < 71 * 32 + 15) //bottom spawm
			{
				m_Input.m_Direction = 1;
			}

			if (m_Core.m_Pos.x > 75 * 32 && m_Core.m_Pos.x < 79 * 32 && m_Core.m_Pos.y > 64 * 32) //hook and aim at the roof before passing the freeze
			{
				m_Input.m_TargetX = 50;
				m_Input.m_TargetY = -180;

				if (m_Core.m_Pos.x > 75 * 32 + 14)
				{
					m_Input.m_Hook = 1;
				}
			}

			if (m_Core.m_Pos.x > 104 * 32 && m_Core.m_Pos.y > 67 * 32 && m_Core.m_Pos.y < 70 * 32 + 10 && m_Core.m_Pos.x < 111 * 32) //hook to get far enough in the last freeze in the bottom spawn way
			{
				m_Input.m_TargetX = 50;
				m_Input.m_TargetY = -180;
				m_Input.m_Hook = 1;
			}

			//Go back if bot is too far in bottomspawnway
			if (m_Core.m_Pos.y < 69 * 32 && m_Core.m_Pos.x > 115 * 32)
			{
				m_Input.m_Direction = -1;
			}

			//Check if bot is on the stairs at the end of bottomspawnway
			if (m_Core.m_Pos.x > 106 * 32 && m_Core.m_Pos.y > 96 * 32 && m_Core.m_Pos.y < 74 * 32 && m_Core.m_Pos.x < 114 * 32)
			{
				m_Input.m_Direction = 1;
			}

			//Check if bot is in his wayblock area but too far left from his plattform
			if (m_Core.m_Pos.x < 101 * 32 && m_Core.m_Pos.y > 73 * 32)
			{
				char aBuf[256];
				str_format(aBuf, sizeof(aBuf), "speed:  x: %f y: %f", m_Core.m_Vel.x, m_Core.m_Vel.y);
				//str_format(aBuf, sizeof(aBuf), "target:  x: %d y: %d", m_Input.m_TargetX, m_Input.m_TargetY);

				//GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "game", aBuf);


				m_Input.m_Direction = 1;
				if (Server()->Tick() % 40 == 0)
				{
					if (m_Core.m_Vel.x < 0.700000f)
					{
						m_Input.m_Jump = 1;
						//GameServer()->SendChat(m_pPlayer->GetCID(), CGameContext::CHAT_ALL, "JUMP!");
					}
				}
			}


			//Check if the bot leaves his loved plattform
			if (m_Core.m_Pos.x < 103 * 32 - 8 && m_Core.m_Pos.y > 80 * 32 + 5)
			{
				m_Input.m_Jump = 1;
			}
			else if (m_Core.m_Pos.x > 108 * 32 + 8 && m_Core.m_Pos.y > 80 * 32 + 5)
			{
				m_Input.m_Jump = 1;
			}


			//Check if the bot is on the 2Tiles plattform at the end of bottomspawnway
			//or somewehre in that direction and go on plattform
			if (m_Core.m_Pos.y > 74 * 32 && m_Core.m_Pos.x > 107 * 32 && m_Core.m_Pos.y < 80 * 32 + 10)
			{
				m_Input.m_Direction = -1;
			}
			else if (m_Core.m_Pos.y > 74 * 32 && m_Core.m_Pos.x < 106 * 32 - 4 && m_Core.m_Pos.y < 80 * 32 + 10)
			{
				m_Input.m_Direction = 1;
			}
			else //on main block spot
			{
				if (m_Core.m_Pos.y > 72 * 32)
				{

					CCharacter *pChr = GameServer()->m_World.ClosestCharType(m_Pos, true);
					if (pChr && pChr->IsAlive())
					{


						if (pChr->m_FreezeTime > 0 && pChr->m_Pos.x - m_Core.m_Pos.x > 5 * 32 + 10)
						{
							m_Input.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_Input.m_TargetY = pChr->m_Pos.y - m_Pos.y;
							m_LatestInput.m_TargetX = pChr->m_Pos.x - m_Pos.x;
							m_LatestInput.m_TargetY = pChr->m_Pos.y - m_Pos.y;
							SetWeapon(3); //grenade
							if (pChr->m_Pos.y < 76 * 32) //if the next player is too high --> aim higher 
							{
								m_Input.m_TargetY = m_Input.m_TargetY - 50;
								m_LatestInput.m_TargetY = m_Input.m_TargetY - 50;
							}

							if (pChr->m_Core.m_Vel.y < 8.f)
							{
								m_LatestInput.m_Fire++;
								m_Input.m_Fire++;
							}

						}
					}
					//other stuff reacting to external influences
					//stay on plattform
					if (m_Core.m_Pos.y < 78 * 32)
					{
						m_Input.m_Hook = 1;
						m_Input.m_TargetY = 200;
						m_Input.m_TargetX = -3;
					}

					//Check if the bot is under the plattform
					if (m_Core.m_Pos.y > 82 * 32 && m_Core.m_Pos.x > 101 * 32 + 10)
					{
						m_Input.m_Direction = -1;
					}



				}
			}
		}
		else if (m_pPlayer->m_DummyMode == 102) //touchup (racer)
		{
			//rest dummy 
			m_Input.m_Hook = 0;
			m_Input.m_Jump = 0;
			m_Input.m_Direction = 0;
			m_LatestInput.m_Fire = 0;
			m_Input.m_Fire = 0;

			//selfkill
			//dyn
			if (m_Core.m_Vel.y == 0.000000f && m_Core.m_Vel.x < 0.01f && m_Core.m_Vel.x > -0.01f && isFreezed)
			{
				if (Server()->Tick() % 20 == 0)
				{
					GameServer()->SendEmoticon(m_pPlayer->GetCID(), 3);
				}

				if (Server()->Tick() % 90 == 0)
				{
					Die(m_pPlayer->GetCID(), WEAPON_SELF);
				}
			}
			//hard
			//quicky low
			if (m_Core.m_Pos.y > 84 * 32 && m_Core.m_Pos.y < 89 * 32 && m_Core.m_Pos.x > 60 * 32 && m_Core.m_Pos.x < 124 * 32)
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}
			//quicky high
			if (m_Core.m_Pos.y > 74 * 32 && m_Core.m_Pos.y < 75 * 32 && m_Core.m_Pos.x > 63 * 32 && m_Core.m_Pos.x < 110 * 32)
			{
				Die(m_pPlayer->GetCID(), WEAPON_SELF);
			}



			//emotes

			if (Server()->Tick() >= m_EmoteTickNext)
			{
				m_pPlayer->m_LastEmote = Server()->Tick();
				int r = rand() % 100;
				GameServer()->SendEmoticon(m_pPlayer->GetCID(), r < 10 ? 1 : r < 55 ? 10 : 9);

				m_EmoteTickNext = Server()->Tick() + Server()->TickSpeed() * 10 + Server()->TickSpeed() * (rand() % 21);
			}


			//focus the floor (flick is funny xD)
			m_Input.m_TargetX = -40;
			m_Input.m_TargetY = 200;


			//Movement
			//spawny area 
			if (m_Core.m_Pos.x > 61 * 32 && m_Core.m_Pos.y > 47 * 32)
			{
				if (m_Core.m_Pos.y < 63 * 32 && m_Core.m_Pos.x < 84 * 32 && m_Core.m_Pos.x > 60 * 32) //at spawn
				{
					if (m_Core.m_Pos.y > 52 * 32 && m_Core.m_Pos.y < 65 * 32 && m_Core.m_Pos.x < 71 * 32)
					{
						if (m_Core.m_Vel.x > -5.4f)
						{
							m_Input.m_Direction = -1;
						}
					}
					else
					{
						m_Input.m_Direction = -1;
					}
				}

				if (m_Core.m_Pos.y > 63 * 32 && m_Core.m_Pos.y < 70 * 32 + 5 && m_Core.m_Pos.x < 108 * 32 || m_Core.m_Pos.x < 83 * 32 && m_Core.m_Pos.y > 63 * 32 && m_Core.m_Pos.y < 71 * 32 + 15
					|| m_Core.m_Pos.y > 52 * 32 && m_Core.m_Pos.y < 71 * 32 && m_Core.m_Pos.x < 66 * 32 //new testy stuff if too far left --> go right
					) //bottom spawm
				{
					m_Input.m_Direction = 1;
				}

				if (m_Core.m_Pos.x > 75 * 32 && m_Core.m_Pos.x < 79 * 32 && m_Core.m_Pos.y > 64 * 32) //hook and aim at the roof before passing the freeze
				{
					m_Input.m_TargetX = 50;
					m_Input.m_TargetY = -180;

					if (m_Core.m_Pos.x > 75 * 32 + 14)
					{
						m_Input.m_Hook = 1;
					}
				}

				if (m_Core.m_Pos.x > 104 * 32 && m_Core.m_Pos.y > 67 * 32 && m_Core.m_Pos.y < 70 * 32 + 10 && m_Core.m_Pos.x < 111 * 32) //hook to get far enough in the last freeze in the bottom spawn way
				{
					m_Input.m_TargetX = 50;
					m_Input.m_TargetY = -180;
					m_Input.m_Hook = 1;
				}

				//Go back if bot is too far in bottomspawnway
				if (m_Core.m_Pos.y < 69 * 32 && m_Core.m_Pos.x > 115 * 32)
				{
					m_Input.m_Direction = -1;
				}

				//Check if bot is on the stairs at the end of bottomspawnway
				if (m_Core.m_Pos.x > 106 * 32 && m_Core.m_Pos.y > 96 * 32 && m_Core.m_Pos.y < 74 * 32 && m_Core.m_Pos.x < 114 * 32)
				{
					m_Input.m_Direction = 1;
				}
			}


			//quicky area
			if (m_Core.m_Pos.y > 74 * 32 && m_Core.m_Pos.y < 89 * 32 && m_Core.m_Pos.x > 56 * 32 && m_Core.m_Pos.x < 124 * 32)
			{
				if (m_Dummy_quickystyle == 0) //grenade
				{
					if (Server()->Tick() % 30 == 0)
					{
						SetWeapon(3);
					}
					m_Input.m_Direction = -1;
					m_Input.m_TargetX = 200;
					m_Input.m_TargetY = 85;
					m_LatestInput.m_TargetX = 200;
					m_LatestInput.m_TargetY = 85;
					if (m_Core.m_Pos.x > 70 * 32 && m_Core.m_Pos.x < 106 * 32 && IsGrounded() /*&& m_FreezeTime == 0*/)
					{
						m_Input.m_Fire++;
						m_LatestInput.m_Fire++;
					}
					if (m_Core.m_Pos.x < 96 * 32 && m_Core.m_Pos.x > 88 * 32)
					{
						m_Input.m_Jump = 1;
					}
				}
				else if (m_Dummy_quickystyle == 1) //hook
				{
					m_Input.m_Direction = -1;
					if (m_Core.m_Pos.x < 104 * 32)
					{
						if (m_Core.m_Pos.y < 78 * 32)
						{
							m_Input.m_TargetX = -80;
							m_Input.m_TargetY = -200;
						}
						else
						{
							m_Input.m_TargetX = -10;
							m_Input.m_TargetY = -200;
						}
						if (m_Core.m_Pos.x < 77 * 32)
						{
							m_Input.m_TargetX = -170;
							m_Input.m_TargetY = -200;
						}


						if (m_Core.m_Pos.y > 77 * 32)
						{
							m_Input.m_Hook = 1;
							if (m_Core.m_Pos.x > 77 * 32 && m_Core.m_Vel.y < -3.4f)
							{
								m_Input.m_Hook = 0;
							}
						}

						if (Server()->Tick() % 40 == 0)
						{
							m_Input.m_Hook = 0;
						}

						if (m_Core.m_Pos.x > 68 * 32 && m_Core.m_Pos.x < 80 * 32 && IsGrounded())
						{
							m_Input.m_Jump = 1;
						}


					}
				}
			}

			//area left from quicky area (the turn up)
			// (m_Core.m_Pos.x > 36 * 32 && m_Core.m_Pos.x < 52 * 32 && m_Core.m_Pos.y > 33 * 32 && m_Core.m_Pos.y < 70 * 32)
			if (m_Core.m_Pos.x > 25 * 32 && m_Core.m_Pos.y > 66 * 32 && m_Core.m_Pos.x < 59 * 32 && m_Core.m_Pos.y < 84 * 32)
			{
				if (m_Core.m_Pos.y > 79 * 32 && IsGrounded())
				{
					m_Input.m_Jump = 1;
				}
				if (m_Core.m_Pos.y < 78 * 32 - 23 && m_Core.m_Pos.y > 68 * 32 && m_Core.m_Pos.x > 53 * 32)
				{
					m_Input.m_Hook = 1;
					m_Input.m_TargetX = -1;
					m_Input.m_TargetY = -200;
					if (Server()->Tick() % 30 == 0)
					{
						m_Input.m_Hook = 0;
					}
				}

				//tricky part the bullet part
				if (m_Core.m_Pos.x > 47 * 32 && m_Core.m_Pos.x < 59 * 32 && m_Core.m_Pos.y > 65 * 32 && m_Core.m_Pos.y < 69 * 32
					|| m_Core.m_Pos.x > 47 * 32 -10 && m_Core.m_Pos.x < 51 * 32 && m_Core.m_Pos.y > 66 * 32 && m_Core.m_Pos.y < 71 * 32
					)
				{
					m_Input.m_Direction = -1;
					m_Input.m_TargetX = -200;
					m_Input.m_TargetY = -160;
					m_Input.m_Hook = 1;
					if (Server()->Tick() % 20 == 0)
					{
						m_Input.m_Hook = 0;
					}
					if (IsGrounded())
					{
						m_Input.m_Jump = 1;
					}
				}

				//small room left under the tricky bullet part
				if (m_Core.m_Pos.x > 28 * 32 && m_Core.m_Pos.x < 50 * 32 && m_Core.m_Pos.y > 70 * 32 - 10 && m_Core.m_Pos.y < 78 * 32)
				{
					if (!m_Dummy_found_pos) // --> find it!
					{
						if (m_Core.m_Pos.x > 42 * 32)
						{
							m_Input.m_Direction = -1;
						}
						else if (m_Core.m_Pos.x < 41 * 32)
						{
							m_Input.m_Direction = 1;
						}
						else
						{
							if (IsGrounded())
							{
								m_Dummy_found_pos = true;
							}
						}

						if (m_Core.m_Pos.x > 44 * 32)
						{
							if (m_Core.m_Vel.y < 4.3f && m_Core.m_Pos.y < 72 * 32 + 10 || m_Core.m_Pos.x > 47 * 32 + 10 && m_Core.m_Pos.y < 74 * 32)
							{
								m_Input.m_TargetX = -200;
								m_Input.m_TargetY = -50;
							}
							else
							{
								m_Input.m_TargetX = -200;
								m_Input.m_TargetY = -200;
							}

							if (m_Core.m_Vel.y > 0.0f)
							{
								m_Input.m_Hook = 1;
							}
							if (m_Core.m_Pos.x < 47 * 32 && m_Core.m_Pos.y < 72 * 32 + 20)
							{
								m_Input.m_Hook = 0;
							}
						}

					}
					else //if at start pos --> start
					{
						m_Input.m_TargetX = 125;
						m_Input.m_TargetY = -240;


						if (m_Core.m_Pos.x > 48 * 32 + 20)
						{
							m_Dummy_swapdir = true;
						}
						if (m_Dummy_swapdir)
						{
							if (m_Core.m_Pos.x < 47 * 32 - 10)
							{
								m_Dummy_swapdir = false;
								m_Dummy_found_pos = false;
							}
						}


						m_Input.m_Direction = 1;
						if (m_Dummy_swapdir)
						{
							m_Input.m_Direction = -1;
						}

						if (m_Core.m_Pos.x > 43 * 32 + 10)
						{
							m_Input.m_Hook = 1;
						}


					}

					//small room jump proection
					if (m_Core.m_Pos.x > 44 * 32 + 10 && m_Core.m_Vel.y > 5.6f && m_Core.m_Pos.y > 73 * 32 + 50)
					{
						m_Input.m_Jump = 1;
					}
					//small room left freeze protection
					if (m_Core.m_Pos.x < 42 * 32 && m_Core.m_Vel.x < -5.5f)
					{
						m_Input.m_Direction = 1;
						m_Input.m_TargetX = 180;
						m_Input.m_TargetY = -220;
						m_Input.m_Hook = 1;
						if (Server()->Tick() % 20 == 0)
						{
							m_Input.m_Hook = 0;
						}
					}

				}
				else
				{
					m_Dummy_swapdir = false;
					m_Dummy_found_pos = false;
				}
			}

			//going up left from spawn (rocketjump up)
			if (m_Core.m_Pos.x > 36 * 32 && m_Core.m_Pos.x < 52 * 32 && m_Core.m_Pos.y > 33 * 32 && m_Core.m_Pos.y < 70 * 32)
			{
				if (m_Core.m_Pos.y > 54 * 32)
				{
					if (m_Core.m_Pos.y > 61 * 32)
					{
						m_Input.m_TargetX = 0;
						m_Input.m_TargetY = 200;
						m_LatestInput.m_TargetX = 0;
						m_LatestInput.m_TargetY = 200;
					}


					//finding rj position
					if (m_Core.m_Pos.x > 46 * 32 - 6)
					{
						m_Input.m_Direction = -1;
					}
					else if (m_Core.m_Pos.x < 45 * 32 + 14)
					{
						m_Input.m_Direction = 1;
					}
					else
					{
						if (IsGrounded() && m_Core.m_Vel.x < 0.01f && m_Core.m_Vel.x > -0.01f)
						{
							m_Input.m_Jump = 1;
						}
						if (m_Core.m_Pos.y > 65 * 32 && m_Core.m_Vel.y < -0.1f)
						{
							m_Input.m_Fire++;
							m_LatestInput.m_Fire++;
						}
					}
				}

				if (m_Core.m_Pos.y < 55 * 32)
				{
					m_Input.m_Direction = 1;
					m_Input.m_TargetX = -180;
					m_Input.m_TargetY = -230;
					m_LatestInput.m_TargetX = -180;
					m_LatestInput.m_TargetY = -230;
					m_Input.m_Hook = 1;
					if (Server()->Tick() % 10 == 0)
					{
						m_Input.m_Hook = 0;
					}
				}
			}
			//TopLane
			if (m_Core.m_Pos.x > 50 * 32 && m_Core.m_Pos.x < 132 * 32 && m_Core.m_Pos.y > 7 * 32 && m_Core.m_Pos.y < 46 * 32)
			{
				m_Input.m_Hook = 0;  //wegen überschneidungen mit dem hochgehen würde er sonst hier hooken was stört 
				m_Input.m_TargetX = -180;
				m_Input.m_TargetY = 77;
				m_LatestInput.m_TargetX = -180;
				m_LatestInput.m_TargetY = 77;
				//the rocketstart
				if (m_Core.m_Pos.x < 58 * 32)
				{
					if (!m_Dummy_rocket_pos)
					{
						if (IsGrounded() && m_Core.m_Vel.x > -3.4f)
						{
							m_Input.m_Direction = -1;
						}
						if (m_Core.m_Pos.x < 50 * 32 + 10 && IsGrounded())
						{
							m_Dummy_rocket_pos = true;
						}
					}
					if (m_Dummy_rocket_pos) //has rocket start pos
					{
						m_Input.m_Direction = 1;
						if (m_Core.m_Pos.x > 51 * 32 + 25)
						{
							m_Input.m_Fire++;
							m_LatestInput.m_Fire++;
						}
					}
				}
				//rocket fly
				if (m_Core.m_Pos.x > 55 * 32 && m_Core.m_Pos.x < 97 * 32 || m_Core.m_Pos.x > 96 * 32 && m_Core.m_Pos.y > 30 * 32)
				{
					m_Input.m_Direction = 1;
					//double jump
					if (m_Core.m_Pos.x > 67 * 32 && m_Core.m_Pos.x < 71 * 32)
					{
						m_Input.m_Jump = 1;
					}
				}
				//prepare aim for swing
				if (m_Core.m_Pos.x > 88 * 32)
				{
					m_Input.m_TargetX = 200;
					m_Input.m_TargetY = -200;
				}
				if (m_Core.m_Pos.x > 96 * 32 && m_Core.m_Pos.y > 30 * 32)
				{
					m_Dummy_swinghook = true;
				}
				if (IsGrounded() || isFreezed)
				{
					m_Dummy_swinghook = false;
				}
				if (m_Dummy_swinghook)
				{
					m_Input.m_Hook = 1;
				}


			}
			else //left toplane --> resett bools
			{
				m_Dummy_rocket_pos = false;
			}



		}
		else
		{
			m_pPlayer->m_DummyMode = 0;
		}