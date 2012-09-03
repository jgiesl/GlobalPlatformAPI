#pragma once

#include "GP_Command.h"

namespace GPAPI
{
	/**
	* Enumerator for types of INSTALL command
	*/
	enum INSTALL_TYPE {
		INSTALL_TYPE_FOR_LOAD = 0x02,					/**< install for load */
		INSTALL_TYPE_FOR_INSTALL = 0x04,				/**< install for install */
		INSTALL_TYPE_FOR_MAKE_SELECTABLE = 0x08,		/**< install for make selectable */
		INSTALL_TYPE_FOR_EXTRADITION = 0x10,			/**< install for extradition */
		INSTALL_TYPE_FOR_PERSONALIZATION = 0x20			/**< install for personalization */
	};

	/**
	* Enumerator for types of privileges
	*/
	enum INSTALL_PRIVILEGES {
		INSTALL_PRIVILEGES_SECURITY_DOMAIN = 0x80,				/**< security domain */
		INSTALL_PRIVILEGES_DAP_VERIFICATION = 0xC0,				/**< DAP verification */
		INSTALL_PRIVILEGES_DELEGATED_MANAGEMENT = 0xA0,			/**< delegated management */
		INSTALL_PRIVILEGES_CARD_LOCK = 0x10,					/**< card lock */
		INSTALL_PRIVILEGES_CARD_TERMINATE = 0x08,				/**< card terminate */
		INSTALL_PRIVILEGES_DEFAULT_SELECTED = 0x04,				/**< default selected */
		INSTALL_PRIVILEGES_CVM_MANAGEMENT = 0x02,				/**< CVM management */
		INSTALL_PRIVILEGES_MANDATED_DAP_VERIFICATION = 0xC1		/**< mandated DAP verification */
	};

	/**
	* Class encapsulates INSTALL command
	*/
	class GP_Install : public GP_Command
	{
	private:

	public:
		GP_Install();
		~GP_Install();

		/**
		* Set all data need for INSTALL for load command
		*
		* @param[in] pLoadFileAID
		*   pointer to buffer containing load file AID
		* @param[in] cLoadFileAID
		*   size of load file AID
		* @param[in] pSecurityDomainAID
		*   pointer to buffer containing security domain AID
		* @param[in] cSecurityDomainAID
		*   size of security domain AID
		* @param[in] pLoadFileHash
		*   pointer to buffer containing hash
		* @param[in] cLoadFileHash
		*   size of hash
		* @param[in] pParameters
		*   pointer to buffer containing parameters
		* @param[in] cParameters
		*   size of parameters
		* @param[in] pToken
		*   pointer to buffer containing token
		* @param[in] cToken
		*   size of token
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetInstallDataForLoad(unsigned char* pLoadFileAID, unsigned long cLoadFileAID, 
			unsigned char* pSecurityDomainAID, unsigned long cSecurityDomainAID, 
			unsigned char* pLoadFileHash, unsigned long cLoadFileHash, 
			unsigned char* pParameters, unsigned long cParameters, 
			unsigned char* pToken, unsigned long cToken);
		/**
		* Set all data need for INSTALL for install command
		*
		* @param[in] pLoadFileAID
		*   pointer to buffer containing load file AID
		* @param[in] cLoadFileAID
		*   size of load file AID
		* @param[in] pModuleAID
		*   pointer to buffer containing executable module AID
		* @param[in] cModuleAID
		*   size of executable module AID
		* @param[in] pApplicationAID
		*   pointer to buffer containing application AID
		* @param[in] cApplicationAID
		*   size of application AID
		* @param[in] nPrivileges
		*   application privileges
		* @param[in] pParameters
		*   pointer to buffer containing parameters
		* @param[in] cParameters
		*   size of parameters
		* @param[in] pToken
		*   pointer to buffer containing token
		* @param[in] cToken
		*   size of token
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetInstallDataForInstall(unsigned char* pLoadFileAID, unsigned long cLoadFileAID, 
			unsigned char* pModuleAID, unsigned long cModuleAID, 
			unsigned char* pApplicationAID, unsigned long cApplicationAID, 
			INSTALL_PRIVILEGES nPrivileges,
			unsigned char* pParameters, unsigned long cParameters, 
			unsigned char* pToken, unsigned long cToken);
		/**
		* Set all data need for INSTALL for install and make selectable
		*
		* @param[in] pLoadFileAID
		*   pointer to buffer containing load file AID
		* @param[in] cLoadFileAID
		*   size of load file AID
		* @param[in] pModuleAID
		*   pointer to buffer containing executable module AID
		* @param[in] cModuleAID
		*   size of executable module AID
		* @param[in] pApplicationAID
		*   pointer to buffer containing application AID
		* @param[in] cApplicationAID
		*   size of application AID
		* @param[in] nPrivileges
		*   application privileges
		* @param[in] pParameters
		*   pointer to buffer containing parameters
		* @param[in] cParameters
		*   size of parameters
		* @param[in] pToken
		*   pointer to buffer containing token
		* @param[in] cToken
		*   size of token
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetInstallDataForInstallAndMakeSelectable(unsigned char* pLoadFileAID, unsigned long cLoadFileAID, 
			unsigned char* pModuleAID, unsigned long cModuleAID, 
			unsigned char* pApplicationAID, unsigned long cApplicationAID, 
			INSTALL_PRIVILEGES nPrivileges,
			unsigned char* pParameters, unsigned long cParameters, 
			unsigned char* pToken, unsigned long cToken);
		/**
		* Set all data need for INSTALL for make selectable
		*
		* @param[in] pApplicationAID
		*   pointer to buffer containing application AID
		* @param[in] cApplicationAID
		*   size of application AID
		* @param[in] nPrivileges
		*   application privileges
		* @param[in] pToken
		*   pointer to buffer containing token
		* @param[in] cToken
		*   size of token
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetInstallDataForMakeSelectable(unsigned char* pApplicationAID, unsigned long cApplicationAID, 
			INSTALL_PRIVILEGES nPrivileges,
			unsigned char* pToken, unsigned long cToken);
		/**
		* Set all data need for INSTALL for extradition
		*
		* @param[in] pSecurityDomainAID
		*   pointer to buffer containing security domain AID
		* @param[in] cSecurityDomainAID
		*   size of security domain AID
		* @param[in] pApplicationAID
		*   pointer to buffer containing application AID
		* @param[in] cApplicationAID
		*   size of application AID
		* @param[in] pToken
		*   pointer to buffer containing token
		* @param[in] cToken
		*   size of token
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetInstallDataForExtradition(unsigned char* pSecurityDomainAID, unsigned long cSecurityDomainAID,
			unsigned char* pApplicationAID, unsigned long cApplicationAID, 
			unsigned char* pToken, unsigned long cToken);
		/**
		* Set all data need for INSTALL for personalization
		*
		* @param[in] pApplicationAID
		*   pointer to buffer containing application AID
		* @param[in] cApplicationAID
		*   size of application AID
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetInstallDataForPersonalization(unsigned char* pApplicationAID, unsigned long cApplicationAID);
	};

}