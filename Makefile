.PHONY: clean All

All:
	@echo "----------Building project:[ 01_Builter_Pattern - Debug ]----------"
	@cd "01_Builter_Pattern" && "$(MAKE)" -f  "01_Builter_Pattern.mk"
clean:
	@echo "----------Cleaning project:[ 01_Builter_Pattern - Debug ]----------"
	@cd "01_Builter_Pattern" && "$(MAKE)" -f  "01_Builter_Pattern.mk" clean
