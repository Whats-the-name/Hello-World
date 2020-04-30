
/**
 * 支付宝支付
 * @param req
 * @param response
 * @throws OperationFailedException
 */
@RequestMapping("alipay/Prepay")
@ResponseBody
public void aliPrepay(@RequestBody AliPrepayReq req, HttpServletResponse response) throws OperationFailedException {
  Set<ConstraintViolation<AliPrepayReq>> constraintViolationSet = validator.validate(req);
  if (constraintViolationSet.size() > 0) {
    throw new OperationFailedException(constraintViolationSet.iterator().next().getMessage());
  }
 
  LibraOrder libraOrder = libraService.findLibraOrderByHashCode(req.getOutTradeNo());
 
  Product product = productRepository.findOne(Long.valueOf(libraOrder.getProduct().getId()));
  if(product == null) { throw new OperationFailedException("该商品不存在"); }
 
  try{
    String form = aliPayService.generateAliPay(req);
 
    if(!"err".equals(form)){
      response.setContentType("text/html;charset=utf-8");
      response.getWriter().write(form);// 直接将完整的表单html输出到页面
      response.getWriter().flush();
    }
  }catch (Exception e){
    throw new OperationFailedException("支付失败");
  }
 
}
