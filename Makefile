.PHONY: clean All

All:
	@echo "----------Building project:[ 03_Composite_Pattern - Debug ]----------"
	@cd "03_Composite_Pattern" && "$(MAKE)" -f  "03_Composite_Pattern.mk"
clean:
	@echo "----------Cleaning project:[ 03_Composite_Pattern - Debug ]----------"
	@cd "03_Composite_Pattern" && "$(MAKE)" -f  "03_Composite_Pattern.mk" clean
