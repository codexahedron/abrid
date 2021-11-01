/**
  \file      irq.h
  \brief     IRQ support.
  \details   This header file is used for interrupt request support.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __IRQ_H
#define __IRQ_H

/**
	\brief Installs the IRQ.
*/
void irq_install();
/**
	\brief Installs an IRQ handler

	Installs an interrupt request handler.
*/
void irq_install_handler();
/**
	\brief Uninstalls an IRQ handler

	Uninstalls an interrupt request handler.
*/
void irq_uninstall_handler();

#endif