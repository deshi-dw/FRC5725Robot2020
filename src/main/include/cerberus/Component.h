#pragma once

class Component {
   public:
   /**
    * Updates the components functionality.
    */
    virtual void update() = 0;
	/**
	 * Initializes the components functionality. Always call this before calling any other functions.
	 */
    virtual void initialize() = 0;
	/**
	 * Deinitializes the components functionality. Used after calling initialize.
	 */
    virtual void deinitialize() = 0;

	/**
	 * Test if the component should update or not.
	 * 
	 * @return true: the component should be updated.
	 * @return false: the component should not be updated.
	 */
    virtual bool updateCondition() {
        return true;
    }

	/**
	 * Test if the component is initialized or not.
	 * 
	 * @return true: the component has been initialized.
	 * @return false: the component has not been initialized.
	 *  
	 * @note If the component is deinitialized after initialization, this will still return false.
	 */
    bool isInitialized() {
        return m_isInitialized;
    }

	/**
	 * Sets the components initialization state. Only for interal use. Calling this will probably break most things.
	 * 
	 * @param initialized: if true, the component is initialized. If false, the component is set to uninitialized.
	 */
    void setInitialized(bool initialized) {
        m_isInitialized = initialized;
    }

   protected:
   /**
    * Internal state of initialization.
    */
    bool m_isInitialized = false;
};