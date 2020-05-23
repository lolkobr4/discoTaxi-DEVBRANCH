# dTaxiSystem
Taxi system with chat based functions. Connected with a Database, designed for uScript for Unturned 3.

# MySQL setup containing:
	Tables:
		taxiRequest:
			ID			=		0		
			requestName =		1
			requestLocation	=	2		// returns X,Y,Z
			accepted		=	3		// returns 0/1
		
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
	people need to "apply"										- DONE
	onplayerconnect get taxidriver permission with DB check		- DONE
	Taxi request list											- DONE
	Basic help cmd												- PARTIAL 
	order a taxi												- DONE
	message requester if taxi is coming							- DONE
	cancel an order												- DONE
	check why everyone can read "new order has been made"
	delete an order after X secs								- DONE
	end an order when job is done. (+jobDone)
	ondisconnect delete entry on db // set accepted to 1.		- DONE

	Accept as driver + createMarker								- PARTIAL
	(cant create a marker. Doesnt even work with player.position)

	
	setup taxiDriver Permission (see above)

	create a variable to delete order after X seconds instead
	of hardcoding it											- DONE
	create function to message the player that it got deleted

# Other
	Create Example Permission Setup for TaxiDriver in XML

# Chat / Notes

	---------------------- Notes box ----------------------
	Added a location at "Order #1 by Radona near" in TaxiRequests
	------------------------------------------------------

	---------------------- Chat box ----------------------

	sure thing
	keep me updated if you decide to keep writing more stuff. ill try to think of some more easier scripts
	kk
	------------------------------------------------------