/*
	This file is part of SHMUP.

    SHMUP is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SHMUP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SHMUP.  If not, see <http://www.gnu.org/licenses/>.
*/    
/*
 *  vis.c
 *  dEngine
 *
 *  Created by fabien sanglard on 09-11-12.
 *  Copyright 2009 Memset software Inc. All rights reserved.
 *
 */

#include "vis.h"
#include "camera.h"
#include "world.h"
#include "timer.h"

#define TRACE_VISSET 0

void VIS_Update(void)
{
	const world_vis_set_update_t* wordVisUpdate;
	const entity_visset_t* entityVisUpdate;
	entity_t* entity;
	int i,j;
	
	//Used for delta frame decoding
	int							toAddCusor, toRemoveCursor;
	
	wordVisUpdate = &camera.currentFrame->visUpdate;
	
	if (TRACE_VISSET)
		Log_Printf("Updating visibilitySet with t=%d and isKey=%d.\n",camera.currentFrame->time,wordVisUpdate->isKey);
	
	if (wordVisUpdate->isKey)
	{
		for (i=0; i  < wordVisUpdate->numVisSets ; i++)
		{
			entityVisUpdate  = &wordVisUpdate->visSets[i] ;
	
			//Log_Printf("	Entity:%d, #indices:%hu\n",entityVisUpdate->entityId, entityVisUpdate->numIndices);
			map[entityVisUpdate->entityId].numIndices = entityVisUpdate->numIndices;
			memcpy(map[entityVisUpdate->entityId].indices, entityVisUpdate->indices, entityVisUpdate->numIndices * sizeof(ushort));	
			
			if (TRACE_VISSET)
			{
				Log_Printf("	For entity %d (numIndices=%hd): \n",entityVisUpdate->entityId,map[entityVisUpdate->entityId].numIndices);
				for (j=0; j <  map[entityVisUpdate->entityId].numIndices ; j++) 
				{
					Log_Printf("%hd--",map[entityVisUpdate->entityId].indices[j]);
				}
				Log_Printf("\n");
			}
			
		}
	}
	else 
	{
		
		for (i=0; i  < wordVisUpdate->numVisSets ; i++)
		{
			entityVisUpdate  = &wordVisUpdate->visSets[i] ;
			entity = &map[entityVisUpdate->entityId];
			
			toAddCusor = 0;
			toRemoveCursor = 0;
			
			// filling void with what need to be added
			while (toAddCusor < entityVisUpdate->numFacesToAdd && toRemoveCursor < entityVisUpdate->numFacesToRemove ) 
			{
				vectorCopy(	&(entity->model->indices[entityVisUpdate->facesToAdd[toAddCusor]])		,   &(entity->indices[entityVisUpdate->facesToRemove[toRemoveCursor]]) ) ;
				
				
				toAddCusor++;
				toRemoveCursor++;
			}
			
			// keep removing by switching with the last element
			while (toRemoveCursor < entityVisUpdate->numFacesToRemove) 
			{
				entity->numIndices -= 3;
				
//				if (simulationTime == 5072)
//					Log_Printf("Flipping tailing: @%hu -> @%hu.\n",entity->numIndices,entityVisUpdate->facesToRemove[toRemoveCursor]);
			
				vectorCopy( &(entity->indices[entity->numIndices]) ,  &(entity->indices[entityVisUpdate->facesToRemove[toRemoveCursor]]) );
				
				
				toRemoveCursor++;
			}
			
			// add at the end and advance numIndices cursor
			while (toAddCusor < entityVisUpdate->numFacesToAdd) 
			{
				vectorCopy( &(entity->model->indices[entityVisUpdate->facesToAdd[toAddCusor]]), &(entity->indices[entity->numIndices]) );
				
				entity->numIndices += 3;
				toAddCusor++;
			}
			
			if (TRACE_VISSET)
			{
				Log_Printf("	For entity %d (numIndices=%hd): \n",entityVisUpdate->entityId,map[entityVisUpdate->entityId].numIndices);
				for (j=0; j <  map[entityVisUpdate->entityId].numIndices ; j++) 
				{
					Log_Printf("%hd--",map[entityVisUpdate->entityId].indices[j]);
				}
				Log_Printf("\n");
			}
		}
	}

}