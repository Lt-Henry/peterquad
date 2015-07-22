

#ifndef _PETERQUAD_SYSTEM_
#define _PETERQUAD_SYSTEM_

namespace com
{
	namespace toxiclabs
	{
		namespace peterquad
		{
			class System
			{
				protected:
				
				float pwm[4];
				float thorttle[4];
			
				public:
				
				System();
				virtual ~System();
				
				virtual void Step();
				
				float GetPwm(unsigned char n);
				void SetPwm(unsigned char n,float pwm);
				
				float GetThorttle(unsigned char n);
				void SetThorttle(unsigned char n,float thorttle);
			};
		}
	}
}

#endif
