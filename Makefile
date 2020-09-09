.PHONY: clean All

All:
	@echo "----------Building project:[ 07_Template_Method - Debug ]----------"
	@cd "07_Template_Method" && "$(MAKE)" -f  "07_Template_Method.mk"
clean:
	@echo "----------Cleaning project:[ 07_Template_Method - Debug ]----------"
	@cd "07_Template_Method" && "$(MAKE)" -f  "07_Template_Method.mk" clean
