# dTaxiSystem
Taxi system with chat based functions. Connected with a Database, designed for uScript for Unturned 3.

# MySQL setup containing:
	Tables:
		taxiRequest:
			ID			=		0		
			requestName =		1
			requestLocation	=	2		// returns X,Y,Z
			accepted		=	3		// returns "True"/"False"
		
		taxiDriver:
			id				=	0	
			steamdID64		=	1
			taxiDriverName	=	2
			jobsDone		=	3

# Permissions
	Permission group name:
		TaxiDriver

	Permissions:
		taxi.job				Everything related to getting/quitting a job
		taxi.order				Perm to order a taxi
		taxi.accept				perm to accept an order. (unneeded? Could be taxi.job)
		taxi.request			To List requests (unneeded? Could be taxi.job)
		taxi.help				To List all commands (unneeded? Could be nothing)
		(Using taxi.job everywhere it fits. cn be changed.)

# Code based:
	disco (https://www.youtube.com/watch?v=G_H0rJj1gJc)
	people need to "apply"										- DONE
	onplayerconnect get taxidriver permission with DB check		- DONE
	Taxi request list											- DONE
	Basic help cmd												- PARTIAL
	
	order a taxi
	cancel an order
	delete an order after X secs
	end an order when job is done.

	Accept as driver + createMarker

	discord whook
	setup taxiDriver Permission
	driver <-> customer // private chat (could be unnecessary)

# Other
	Create Example Permission Setup for TaxiDriver in XML
# Chat / Notes

	---------------------- Notes box ----------------------
	Please check  in orderTaxi if the position will be saved correctly
	as 13,3,7 or if it throws an error. Wasnt sure if uScript detects it as a string.
	in (line 92)

	Ran the file on my server, no syntax errors so far. Haven't tried each command
	individually, though.

	------------------------------------------------------

	---------------------- Chat box ----------------------


	------------------------------------------------------