.PHONY: clean All

All:
	@echo "----------Building project:[ 06_Abstract_Factory - Debug ]----------"
	@cd "06_Abstract_Factory" && "$(MAKE)" -f  "06_Abstract_Factory.mk"
clean:
	@echo "----------Cleaning project:[ 06_Abstract_Factory - Debug ]----------"
	@cd "06_Abstract_Factory" && "$(MAKE)" -f  "06_Abstract_Factory.mk" clean
