/*
 * Copyright 2012 KTH
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
 * OF ANY KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */

/* 
 * File:   lock.h
 * Author: alpsayin
 *
 * Created on April 1, 2012, 12:18 AM
 */

#ifndef LOCK_H
#define	LOCK_H

#ifdef	__cplusplus
extern "C" {
#endif

char *mbasename(char *s, char *res, int reslen);
int lockfile_create(void);
void lockfile_remove(void);
int have_lock_dir(char* dial_tty);
int get_lock(char* dial_tty);
int getLockRetries(void);
int decrementLockRetries(void);


#ifdef	__cplusplus
}
#endif

#endif	/* LOCK_H */

