//
//  AQ.h
//  Dodge
//
//  Created by fabien sanglard on 22/06/09.
//  Copyright 2009 Memset software Inc 2009. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface AQ : NSObject {
}

- (void)initAudio;
- (void)loadSoundTrack:(NSString *)file startAt:(int)startAt ;
- (void)start;
- (void)end;
- (void)pause;
- (void)resume;


@end
