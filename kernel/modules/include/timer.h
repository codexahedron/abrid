/**
  \file      timer.h
  \brief     Provides timer support to the kernel
  \details   Allows the kernel to get the seconds elapsed since the OS was loaded, sleeping, and more.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __TIMER_H
#define __TIMER_H

/**
	\brief Installs the timer
*/
void timer_install();
/**
	\brief Waits `val` seconds
	\param{in} val The amount of seconds to wait
*/
void timer_wait(int val);

/**
	\brief Gets the seconds elapsed since Abrid was loaded
	\returns The amount of seconds elapsed since Abrid was loaded
*/
int get_tracked_seconds();

#endif
