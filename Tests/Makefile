TARGETS = Math/Point \
		  Math/Vector \
		  Math/Sphere \
		  Math/Solutions/Linear \
		  Math/Solutions/MatrixInv \
		  Multithreading/Queue \
		  Multithreading/Pool \
		  Raytracing/Ray

fclean:
	@$(foreach dir, $(TARGETS), $(MAKE) fclean -C $(dir); )

test:
	@$(foreach dir, $(TARGETS), $(MAKE) re -C $(dir); )
	@$(foreach dir, $(TARGETS), ./$(dir)/test; )
	@$(foreach dir, $(TARGETS), $(MAKE) fclean -C $(dir); )
